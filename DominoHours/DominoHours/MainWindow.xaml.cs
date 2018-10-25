using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Reflection;

namespace DominoHours
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

        }

        private void CreateRecord_Click(object sender, RoutedEventArgs e)
        {

                Dates.AddToList(Dates.DateList, TextBox_From.Text, TextBox_To.Text);
            if (Dates.DateList.Count != 0)
            {
                Dates Today = Dates.DateList.Last();

                //Add new record and refresh UI
                Record_DataGrid.Items.Refresh();
                RefreshStatistics(StatBox);
                if (Dates.CheckToday(Dates.DateList))
                {
                    CreateRecord.IsEnabled = false;
                }
            }
      
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            //Set Record_DataGrid source
            Record_DataGrid.ItemsSource = Dates.DateList;

            if (File.Exists(Dates.path))
            {

                //Set textbox date
                TodayText.Text = "Create record for: \n" + DateTime.Today.ToShortDateString();
                TodayText.TextAlignment = TextAlignment.Center;

                //Load records from file
                Dates.LoadList(Dates.DateList);

                //Check if today is already recorded, no duplicates
                if (Dates.CheckToday(Dates.DateList))
                {
                    MessageBox.Show("Today is already recorded.", "Warning", MessageBoxButton.OK, MessageBoxImage.Asterisk);
                    CreateRecord.IsEnabled = false;
                }

                //Show statistics
                RefreshStatistics(StatBox);
            }
            else
            {
                //to be implemented
            }

        }

        public void RefreshStatistics(TextBlock StatTextBlock)
        {
            string FirstCutoffDate = "2018.10.22.", NextPayDate = "2018.10.26";
            double SumHours = 0, HourlyWage = 7.83;

            DateTime d2; DateTime.TryParse(FirstCutoffDate, out d2);

            foreach (var date in Dates.DateList)
            {
                DateTime d1; DateTime.TryParse(date.Date, out d1);
 
                if ((d1 - d2).TotalDays % 28 == 0)
                {
                    NextPayDate = d1.AddDays(32).ToShortDateString();
                    SumHours = 0;
                }
                TimeSpan.TryParse(date.Worked, out TimeSpan timeSpan);
                SumHours += timeSpan.TotalHours;
            }
            StatTextBlock.Text = "Statistics:\nHours worked: " + SumHours.ToString("0.00") +
                "\nSalary: " + (SumHours * HourlyWage).ToString("0.00") + " £ on " + NextPayDate + "\n" +
                "Expected (taxed) salary: " + CalculateTax(SumHours*HourlyWage).ToString("0.00") + " £" +
                "\nTax amount: " + ((SumHours * HourlyWage) - CalculateTax(SumHours * HourlyWage)).ToString("0.00") + " £"; 

        }

        //Calculate taxed salary with 2018 data, and 20% taxrate (L1185 taxcode)
        public static double CalculateTax(double SumInPounds)
        {
            double TaxedSum = 0, TaxFreeIncome, TaxedIncome, PersonalAllowance = 11850/12;

            TaxFreeIncome = SumInPounds > PersonalAllowance ? PersonalAllowance : SumInPounds;
            TaxedIncome = (SumInPounds - TaxFreeIncome) * 0.8;

            TaxedSum = TaxFreeIncome + TaxedIncome;

            return TaxedSum;
        }

        private void ResetRecord_Click(object sender, RoutedEventArgs e)
        {
            //Removes previous record and writes the new one
            Dates.DateList.Remove(Dates.DateList.Last());
            CreateRecord.RaiseEvent(new RoutedEventArgs(Button.ClickEvent));
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            //Save to file, must delete to avoid duplicates (more memory friendly than iterating through the file and removing last line)
            string FirstCutoffDate = "2018.09.24.", NextPayDate = "2018.09.28";
            double SumHours = 0, HourlyWage = 7.83;
            
            DateTime d2; DateTime.TryParse(FirstCutoffDate, out d2);

            File.Delete(Dates.path);
            using (var file = File.AppendText(Dates.path))
            {
                foreach (Dates date in Dates.DateList)
                {
                    DateTime d1; DateTime.TryParse(date.Date, out d1);
                    file.WriteLine(date.Date + " " + date.From + " " + date.To);

                    if ((d1 - d2).TotalDays % 28 == 0)
                    {
                        File.Delete(Dates.path_Statistics);
                        using (var fileStat = File.AppendText(Dates.path_Statistics))
                        {
                            Dates.WriteStatistics(fileStat, Dates.DateList, HourlyWage, SumHours, date.Date);
                        }

                        NextPayDate = d1.AddDays(32).ToShortDateString();
                        SumHours = 0;
                    }
                    TimeSpan.TryParse(date.Worked, out TimeSpan timeSpan);
                    SumHours += timeSpan.TotalHours;
                }
            }

        }
    }
}
