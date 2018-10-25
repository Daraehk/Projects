using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp3
{
    class Roulette
    {
        public int Num { get; set; }
        public string Color { get; set; }
        public string Size { get; set; }
    }
    class CasinobetCalculator
    {

        //Show the table of winnings/bets per round based on given base bet and mode

        static void WinTable(float bet, bool turbo)
        {
            int rounds = 10;
            Console.Write("\nChance to win and bets per round: \n");
            for(int i = 1; i <= rounds; i++)
            {
                if(i < 10)
                Console.Write("   " + i + "    ");
                else
                Console.Write("   " + i + "   ");

            }
            var n = 0.5;
            for (int i = 1; i <= rounds; i++)
            {
                Console.Write("" + (1-n).ToString("P2") + " ");
                n *= 0.5;
            }
            double BetCalc = bet/2;
            for (int i = 1; i <= rounds; i++)
            {             
                Console.Write(" ");
                if (i <= 10)
                {
                    if (turbo && BetCalc >= bet)
                        BetCalc = BetCalc * 2 + bet;
                    else
                        BetCalc *= 2;

                    if (BetCalc < 10)
                        Console.Write("" + BetCalc.ToString(" " + "0.0") + "   ");
                    else Console.Write("" + BetCalc.ToString("00.0") + "   ");
                }
                else
                    Console.Write(BetCalc.ToString("00.0"));

            }
            Console.Write("\n\n");
        }



        static void Main(string[] args)
        {

            //Initialization

            List<Roulette> Numbers = new List<Roulette>();
            string[] buffer;
            float bet = 0;
            bool turbo = false;

            float pair, color, size;
            size = 0.1F;
            color = 0.1F;
            pair = 0.1F;
            int num;
            bool low, even, red;
            low = true;
            even = true;
            red = true;

            Console.WriteLine("Turbo mode? [Y/N]");
            if (String.Equals(Console.ReadLine(), "y", StringComparison.CurrentCultureIgnoreCase))
                turbo = true;

                Console.WriteLine("What bet do you play? (default: 0,1) ");
            try
            {
                bet = float.Parse(Console.ReadLine());
            }
            catch(Exception ex)
            {
                bet = 0.1F;
            }
            Console.Write("\n");
            WinTable(bet, turbo);
            Console.WriteLine("Type WinTable or WT to see it again.\n");


            //Read numbers from file

            using (var streamReader = new StreamReader("numbers.txt"))
            {
                string line;
                while ((line = streamReader.ReadLine()) != null)
                {
   
                    buffer = line.Split(';');
                    Roulette number = new Roulette();
                    number.Num = int.Parse(buffer[0]);
                    number.Color = buffer[1];
                    number.Size = buffer[2].ToString();
                    Numbers.Add(number);
                }
            }

            //Warming up the calculator

            Console.WriteLine("***Don't play yet, just give me numbers!***");
            string p = "odd", c = "black", s = "high";
            Roulette previous, actual;
            num = int.Parse(Console.ReadLine());
            previous = Numbers.Find(x => x.Num == num);
            if (previous.Num % 2 == 0) p = "even";
            else
            {
                even = false;
                p = "odd";
            }
            if (previous.Color == "red") c = "red";
            else
            {
                red = false;
                c = "black";
            }
            if (previous.Size == "low") s = "low";
            else
            {
                low = false;
                s = "high";
            }
            num = int.Parse(Console.ReadLine());
            previous = Numbers.Find(x => x.Num == num);
            if (previous.Num % 2 == 0 && p == "odd") p = "odd";
            else p = "even";
            if (previous.Color == "red" && c == "black") c = "black";
            else c = "red";
            if (previous.Size == "low" && s == "high") s = "high";
            else s = "low";

            int counter = 0;

            //Calculator loop

            while (true)
            {
                try
                {
                    num = int.Parse(Console.ReadLine());
                }

                //Format and value check

                catch(FormatException ex)
                {
                    Console.WriteLine("\nDo you want to see the WinTable? [y/n]");
                    if (String.Equals(Console.ReadLine(), "y", StringComparison.CurrentCultureIgnoreCase))
                    {
                        WinTable(bet, turbo);
                        Console.WriteLine("Next number: \n");
                        continue;
                    }
                    else
                    {
                        Console.WriteLine("Next number: \n");
                        continue;
                    }
                }
                if(num < -1 || num > 36)
                {
                    Console.WriteLine("No such thing in the roulette, try again...");
                    continue;
                }

                if (num == -1) break;
                if (num == 0)
                {
                    pair = pair * 2 + bet;
                    color = color * 2 + bet;
                    size = size * 2 + bet;
                    if(counter != 0)
                    Console.WriteLine("Next bet: " + p + " " + pair + " " + s + " " + size + " " + c + " " + color);

                }
                else

                //Calculating bets from previous numbers

                {
                    actual = Numbers.Find(x => x.Num == num);

                    if (actual.Num % 2 == 0 && previous.Num % 2 == 0) pair = pair * 2;
                    if (actual.Num % 2 == 1 && previous.Num % 2 == 1) pair = pair * 2;
                    if (actual.Num % 2 == 0 && previous.Num % 2 == 1) pair = bet;
                    if (actual.Num % 2 == 1 && previous.Num % 2 == 0) pair = bet;

                    if (actual.Num % 2 == 0 && previous.Num % 2 == 0 && even == true) even = true;
                    if (actual.Num % 2 == 1 && previous.Num % 2 == 0) even = true;
                    if (actual.Num % 2 == 0 && previous.Num % 2 == 1) even = false;
                    if (actual.Num % 2 == 1 && previous.Num % 2 == 1 && even == false) even = false;
                    if (actual.Num % 2 == 1 && previous.Num % 2 == 1 && even == true) even = true;

                    if (actual.Color == "Red" && previous.Color == "Red") color = color * 2;
                    if (actual.Color == "Black" && previous.Color == "Black") color = color * 2;
                    if (actual.Color == "Red" && previous.Color == "Black") color = bet;
                    if (actual.Color == "Black" && previous.Color == "Red") color = bet;

                    if (actual.Color == "Red" && previous.Color == "Red" && red == true) red = true;
                    if (actual.Color == "Black" && previous.Color == "Red") red = true;
                    if (actual.Color == "Red" && previous.Color == "Black") red = false;
                    if (actual.Color == "Black" && previous.Color == "Black" && red == false) red = false;
                    if (actual.Color == "Black" && previous.Color == "Black" && red == true) red = true;

                    if (actual.Size == "Low" && previous.Size == "Low") size = size * 2;
                    if (actual.Size == "High" && previous.Size == "High") size = size * 2;
                    if (actual.Size == "High" && previous.Size == "Low") size = bet;
                    if (actual.Size == "Low" && previous.Size == "High") size = bet;

                    if (actual.Size == "Low" && previous.Size == "Low" && low == true) low = true;
                    if (actual.Size == "High" && previous.Size == "Low") low = true;
                    if (actual.Size == "Low" && previous.Size == "High") low = false;
                    if (actual.Size == "High" && previous.Size == "High" && low == false) low = false;
                    if (actual.Size == "High" && previous.Size == "High" && low == true) low = true;

                    if (!even) p = "odd";
                    else p = "even";

                    if (!low) s = "high";
                    else s = "low";

                    if (!red) c = "Black";
                    else c = "Red";

                    //turbo
                    if (turbo && pair != bet)
                        pair += bet;
                    if (turbo && color != bet)
                        color += bet;
                    if (turbo && size != bet)
                        size += bet;
                    

                    if (counter != 0)
                    {
                        Console.WriteLine("Next bet: " + p + " " + pair.ToString("0.0") + " " + s + " " + size.ToString("0.0") + " " + c + " " + color.ToString("0.0"));

                    }
                    else
                    {
                        Console.WriteLine("***After the next number can start playing!***\n");
                        counter++;
                    }
                        previous = actual;


                }
            }
        }
    }
}
