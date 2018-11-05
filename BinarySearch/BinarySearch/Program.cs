using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BinarySearch
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> numbers = new List<int> { };
            Random number = new Random();

            for (int i = 0; i < 10000; i++)
            {
                int buffer = int.Parse(number.Next(0,100000).ToString());
                numbers.Add(buffer);
                number = new Random(number.Next());
                Console.WriteLine(numbers[i]);
            }
            Order(numbers);

            int result = 0, numberofguesses = 0;
            do
            {
                result = BinarySearch(numbers, int.Parse(Console.ReadLine()));
                if (result == 0)
                {
                    
                    Console.WriteLine("Number not present in the list, try a different one:");
                    Console.WriteLine("Number of guesses: " + ++numberofguesses);
                }
                else
                {
                    Console.WriteLine("Number is at index: " + result + " You win!");
                    numberofguesses = 0;
                }
            } while (true);

        }

        static void Order(List<int> Array)
        {
            int i = 0, j = 0;
            while(i < Array.Count)
            {
                j = i;
                while(j > 0 && Array[j-1] > Array[j])
                {
                    int buffer = Array[j];
                    Array[j] = Array[j - 1];
                    Array[j - 1] = buffer;
                    j--;
                }
                i++;
            }
        }

        static int BinarySearch(List<int> array, int searched)
        {

            int min = 0;
            int max = array.Count - 1;

            int buff = (min + max) / 2;
            do
            {
                buff = (min + max) / 2;
                if (array[buff] != searched)
                {
                    if (array[buff] < searched)
                        min = buff + 1;
                    else max = buff - 1;
                    Console.WriteLine(min + " " + max);
                }
                else return buff;
            } while (min < max);
            return 0;
        }
    }
}
