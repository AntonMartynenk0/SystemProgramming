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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace lab5
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Calculator : Page
    {
        double a, b;
        int count;
        bool sign = true;
        Double resultValue = 0;
        bool isOperationValue = false;

        public Calculator()
        {
            this.InitializeComponent();
        }

        // Очистка введенных значений
        private void buttonCe_Click(object sender, RoutedEventArgs e)
        {
            textBoxResult.Text = "0";
        }

        private void buttonC_Click(object sender, RoutedEventArgs e)
        {
            textBoxResult.Text = "0";
            resultValue = 0;
            textBlock.Text = " ";
        }

        private void buttonDel_Click(object sender, RoutedEventArgs e)
        {
            if (!textBoxResult.Text.Contains('E'))
            {
                if (textBoxResult.Text == "NaN")
                {
                    textBoxResult.Text = "0";
                    textBlock.Text = "";
                }
                if (!textBoxResult.Text.Contains('-') || (!(textBoxResult.Text.Length == 2)))
                {
                    if ((textBoxResult.Text == "") || (textBoxResult.Text == "0") || (textBoxResult.Text.Length == 1))
                    {
                        textBoxResult.Text = "0";
                    }
                    else
                    {
                        textBoxResult.Text = textBoxResult.Text.Remove(textBoxResult.Text.Length - 1, 1);
                    }
                }
                else if (textBoxResult.Text.Contains('-') || ((textBoxResult.Text.Length == 2)))
                {
                    textBoxResult.Text = "0";
                }
            }
        }

        private void buttonChangeSign_Click(object sender, RoutedEventArgs e)
        {
            // Смена знака на противоположное
            if (textBoxResult.Text != "0")
            {
                if (sign == true)
                {
                    textBoxResult.Text = "-" + textBoxResult.Text;

                    sign = false;
                }
                else
                {
                    textBoxResult.Text = textBoxResult.Text.Replace("-", "");
                    sign = true;
                }
            }
        }

        private void buttonPlus_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (textBoxResult.Text == "NaN")
                {
                    textBoxResult.Text = "0";
                }
                a = double.Parse(textBoxResult.Text);
                textBoxResult.Text = "";
                count = 1;
                textBlock.Text = a.ToString() + "+";
                sign = true;
            }
            catch (Exception) { }
        }

        private void buttonMinus_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (textBoxResult.Text == "NaN")
                {
                    textBoxResult.Text = "0";
                }
                a = double.Parse(textBoxResult.Text);
                textBoxResult.Text = "";
                count = 2;
                textBlock.Text = a.ToString() + "-";
                sign = true;
            }
            catch (Exception) { }
        }

        private void buttonMul_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (textBoxResult.Text == "NaN")
                {
                    textBoxResult.Text = "0";
                }
                a = double.Parse(textBoxResult.Text);
                textBoxResult.Text = "";
                count = 3;
                textBlock.Text = a.ToString() + "*";
                sign = true;
            }
            catch (Exception) { }
        }

        private void buttonDiv_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (textBoxResult.Text == "NaN")
                {
                    textBoxResult.Text = "0";
                }
                a = double.Parse(textBoxResult.Text);
                textBoxResult.Text = "";
                count = 4;
                textBlock.Text = a.ToString() + "/";
                sign = true;
            }
            catch (Exception) { }
        }

        private void buttonEqual_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                calculate();
                if ((Double.Parse(textBoxResult.Text) > 9999999999999999) || (Double.Parse(textBoxResult.Text) < -9999999999999999))
                {
                    textBoxResult.Text = "NaN";
                }
                else
                {
                    textBlock.Text = "";
                    resultValue = Double.Parse(textBoxResult.Text);
                    textBlock.Text = " ";
                }
            }
            catch (Exception) { }
        }

        private void buttonCos_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Cos(Convert.ToDouble(textBoxResult.Text));
            textBoxResult.Text = resultValue.ToString();
        }

        private void buttonSis_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Sin(Convert.ToDouble(textBoxResult.Text));
            textBoxResult.Text = resultValue.ToString();
        }

        private void buttonTn_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Tan(Convert.ToDouble(textBoxResult.Text));
            textBoxResult.Text = resultValue.ToString();
        }

        private void buttonSecondPow_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Pow(Convert.ToDouble(textBoxResult.Text), 2);
            textBoxResult.Text = resultValue.ToString();
        }

        private void buttonThirdPow_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Pow(Convert.ToDouble(textBoxResult.Text), 3);
            textBoxResult.Text = resultValue.ToString();
        }

        private void buttonSquareRoot_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Sqrt(Convert.ToDouble(textBoxResult.Text));
            textBoxResult.Text = resultValue.ToString();
        }

        private void buttonLogarithm_Click(object sender, RoutedEventArgs e)
        {
            resultValue = Math.Pow(10, Convert.ToDouble(textBoxResult.Text));
            textBoxResult.Text = resultValue.ToString();
        }

        // Клик на любую кнопку
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (textBoxResult.Text == "NaN")
                {
                    textBoxResult.Text = "0";
                }
                if ((textBoxResult.Text == "0") || (isOperationValue == true))
                {
                    textBoxResult.Text = "";
                }
                isOperationValue = false;
                Button button = (Button)sender;
                textBoxResult.Text = textBoxResult.Text + button.Content;
            }
            catch (Exception)
            {
                textBoxResult.Text = "0";
                textBlock.Text = " ";
            }
        }

        private void calculate()
        {
            switch (count)
            {
                case 1:
                    b = a + float.Parse(textBoxResult.Text);
                    textBoxResult.Text = b.ToString();
                    break;
                case 2:
                    b = a - float.Parse(textBoxResult.Text);
                    if (b < 0)
                        sign = false;
                    textBoxResult.Text = b.ToString();
                    break;
                case 3:
                    b = a * float.Parse(textBoxResult.Text);
                    textBoxResult.Text = b.ToString();
                    break;
                case 4:
                    if (float.Parse(textBoxResult.Text) != 0)
                    {
                        b = a / float.Parse(textBoxResult.Text);
                        textBoxResult.Text = b.ToString();
                    }
                    else
                    {
                        textBoxResult.Text = "NaN";
                    }
                    break;
                case 5:
                    try
                    {
                        if (a > 0)
                        {
                            double f = 1;
                            for (int i = 1; i <= a; i++)
                                f *= (double)i;
                            textBoxResult.Text = f.ToString();
                        }
                        else
                            textBoxResult.Text = "NaN";
                    }
                    catch (Exception) { }
                    break;
                default:
                    break;
            }
        }
    }
}
