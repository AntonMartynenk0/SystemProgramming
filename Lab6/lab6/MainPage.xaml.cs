using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.FileProperties;
// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace lab6
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private StorageFolder currentDirectory;

        public MainPage()
        {
            this.InitializeComponent();
            Binding binding = new Binding();
            binding.ElementName = "listBoxMain";
        }
        StorageFolder folder;
        private async void buttonCharheDir_Click(object sender, RoutedEventArgs e)
        {
            FolderPicker folderPicker = new FolderPicker();
            folderPicker.ViewMode = PickerViewMode.Thumbnail;
            folderPicker.FileTypeFilter.Add(".txt");
            folder = await folderPicker.PickSingleFolderAsync();
            getItemsList(folder);
        }

        private async void getItemsList(StorageFolder folder)
        {
            if (folder != null)
            {
                listBoxMain.Items.Clear();
                textBoxCurrDir.Text = folder.Path.ToString();

                ListBoxItem listBoxItem = new ListBoxItem();
                listBoxItem.Content = "Type\tName\t\t\t\tDate of Creation\t\t\tSize";
                listBoxMain.Items.Add(listBoxItem);
                currentDirectory = folder;
                IReadOnlyList<IStorageItem> itemsList = await folder.GetItemsAsync();
                foreach (var item in itemsList)
                {
                    listBoxItem = new ListBoxItem();
                    listBoxItem.Tag = item;
                    if (item is StorageFolder)
                    {
                        listBoxItem.Content = "Folder\t"+item.Name+ "\t\t\t" + item.DateCreated.DateTime;
                    }
                    else
                    {
                        BasicProperties properties = await item.GetBasicPropertiesAsync();
                        listBoxItem.Content = "File\t" + item.Name+ "\t\t\t" + item.DateCreated.DateTime+ "\t\t\t" + GetSize(properties.Size);
                    }
                    listBoxMain.Items.Add(listBoxItem);
                    listBoxItem.DoubleTapped += Navigate;
                }
            }
        }

        private async void buttonCreateFolder_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrEmpty(textBoxCreateFolder.Text))
            {
                try
                {
                    await currentDirectory.CreateFolderAsync(textBoxCreateFolder.Text);
                }
                catch (Exception)
                { }
                getItemsList(currentDirectory);
            }
        }

        private async void buttonDeleteFolder_Click(object sender, RoutedEventArgs e)
        {
            if (listBoxMain.SelectedItem == null)
                return;

            ListBoxItem listBoxItem = (ListBoxItem)listBoxMain.SelectedItem;
            if (listBoxItem.Tag is StorageFolder)
            {
                StorageFolder folder = (StorageFolder)listBoxItem.Tag;
                await folder.DeleteAsync();
            }
            getItemsList(currentDirectory);
        }

        private string GetSize(ulong byteSize)
        {
            ulong finalSize = byteSize;
            string endString = " Б";
            if (finalSize > 1024)
            {
                endString = " КБ";
                finalSize /= 1024;
            }

            if (finalSize > 1024)
            {
                endString = " МБ";
                finalSize /= 1024;
            }

            if (finalSize > 1024)
            {
                endString = " ГБ";
                finalSize /= 1024;
            }
            return finalSize + endString;
        }

        private void Navigate(object sender, DoubleTappedRoutedEventArgs e)
        {
            ListBoxItem listBoxItem = (ListBoxItem)sender;
            if (listBoxItem.Tag is StorageFolder)
            {
                getItemsList((StorageFolder)listBoxItem.Tag);
            }
        }
    }
}
