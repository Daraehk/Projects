using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace DominoHours
{
    public class Dates
    {
        //Members
        private DateTime _date;
        public string Date
        {
            get { return _date.ToShortDateString(); }
            set { DateTime.TryParse(value, out _date); }
        }
        private DateTime _from;
        public string From
        {
            get {  return _from.ToShortTimeString(); }
            set {  DateTime.TryParse(value, out _from); }
        }
        private DateTime _to;
        public string To
        {
            get { return _to.ToShortTimeString(); }
            set { DateTime.TryParse(value, out _to); }
        }
        private TimeSpan _workedHours;
        public string Worked
        {
            get { return _to.Subtract(_from).ToString(@"hh\:mm"); }
            set { TimeSpan.TryParse(value, out _workedHours); }
        }
        public static List<Dates> DateList { get; set; } = new List<Dates>();

        //Get file paths
        public static string path = System.IO.Path.GetDirectoryName(Assembly.GetEntryAssembly().Location).ToString() + "worked_hours.doc";
        public static string path_Statistics = System.IO.Path.GetDirectoryName(Assembly.GetEntryAssembly().Location).ToString() + "Monthly_Statistics.doc";

        //Methods

        public static void AddToList(List<Dates> dates, string From, string To)
        {
            //Get values from DateTime.Today() and source          
            Dates Today = new Dates();
            {
                Today.Date = DateTime.Today.ToString();
                Today.From = From;
                Today.To = To;
            }

            //Check input validity. If format or range not valid, DateTime.TryParse gives 0:00
            if (Today.From == "0:00" || Today.To == "0:00")
            {
                MessageBox.Show("The given time input is not supported. Please use \"hh:mm\" with 24h format.", "Wrong Time Format", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            dates.Add(Today);
        }

        public static void LoadList(List<Dates> dates)
        {
            //Check file
            if (!File.Exists(path))
                return;

            //Read records
            using (var file = new StreamReader(path))
            {
                string Buff;
                while ((Buff = file.ReadLine()) != null)
                {
                    string[] Buffsplit = Buff.Split(' ');
                    Dates Date = new Dates();
                    {
                        Date.Date = Buffsplit[0];
                        Date.From = Buffsplit[1];
                        Date.To = Buffsplit[2];
                    }
                    dates.Add(Date);
                }
            }

        }

        public static bool CheckToday(List<Dates> dates)
        {
            Dates LastRecord = dates.Last();
            if (LastRecord.Date == DateTime.Today.ToShortDateString())
                return true;
            return false;
        }

        public static void WriteStatistics(StreamWriter file, List<Dates> DataList, double HourlyWage, double SumHours, string PayDate)
        {

            file.WriteLine("4 week summary (" + PayDate + ")\n");

            file.WriteLine("    Day        From     To    Hours\n");
            int DaysWorked = 0;
            foreach(var date in DataList)
            {

                if (DateTime.Parse(date.Date) < DateTime.Parse(PayDate) && DateTime.Parse(date.Date) >= DateTime.Parse(PayDate).AddDays(-28))
                {
                    DaysWorked++;
                    file.WriteLine(date.Date + " | " + date.From + " | " + date.To + " | " + date.Worked);
                }
            }
            file.WriteLine( "\nDays worked: " + DaysWorked +
                            "\nHours worked: " + SumHours +
                            "\nAverage hours per workday: " + SumHours/DaysWorked +
                            "\nAverage hours per day: " + SumHours/28 +
                            "\nSalary: " + (SumHours * HourlyWage).ToString("0.00") + " £\n" +
                            "Expected (taxed) salary: " + MainWindow.CalculateTax(SumHours * HourlyWage).ToString("0.00") + " £" +
                            "\nTax amount: " + ((SumHours * HourlyWage) - MainWindow.CalculateTax(SumHours * HourlyWage)).ToString("0.00") + " £");
            file.WriteLine("\n#########################################################################\n");



        }


    }
}
