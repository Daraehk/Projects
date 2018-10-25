using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Generics
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            /*
            Lists (allows duplicates)
            * Stack<T> LIFO
            * Queue<T> FIFO
            * List<T> unordered, random integer indexing
            * LinkedList<T> unordered, linked
            Sets (no dublicates)
            * HashSet<T> unordered
            * SortedSet<T> sorted (IComparer<T>)
            Associative lists
            * SortedList<TKey, TValue> 
            * 
            */
            PalCBX.SelectedIndex = 0;
            PalTB.Text = "1 2 3 2 1";

            AnaCBX.SelectedIndex = 3;
            AnaTB1.Text = "dream";
            AnaTB2.Text = "armed";

        }

        //Palindrome

        public static bool IsPalindromic<T>(IEnumerable<T> input)
            where T:IComparable
        {
            bool status = true;
            Stack<T> buffer = new Stack<T>();
            foreach (T element in input)
                buffer.Push(element);
            for (int i = 0; i < input.Count(); i++)
                if (buffer.Pop().CompareTo(input.ElementAt(i)) != 0)
                    status = false;

            return status;
        }

        private void PalBtn_Click(object sender, EventArgs e)
        {
            switch (PalCBX.SelectedIndex)
            {
                case 0:
                    try
                    {
                        MessageBox.Show(IsPalindromic(PalTB.Text.Split(' ').Select(int.Parse).ToList()).ToString());
                        break;
                    }
                    catch(Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
                    
                case 1:
                    try
                    {
                        MessageBox.Show(IsPalindromic(PalTB.Text.Split(' ').Select(float.Parse).ToList()).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
                case 2:
                    try
                    {
                        MessageBox.Show(IsPalindromic(PalTB.Text).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
                case 3:
                    try
                    {
                        MessageBox.Show(IsPalindromic(PalTB.Text.Split(' ').ToList()).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
            }
        }

        //Anagram

        public static bool IsAnagram<T>(IEnumerable<T> first, IEnumerable<T> second)
        {
            SortedList<T, int> val = new SortedList<T, int>();

            foreach(T element in first)
            {
                if (!val.ContainsKey(element))
                    val.Add(element, 1);
                else
                    val[element]++;
            }

            foreach(T element in second)
            {
                if (val.ContainsKey(element))
                    val[element]--;
            }

            foreach (T element in val.Keys)
                if (val[element] != 0)
                    return false;
            return true;
        }

        private void AnaBtn_Click(object sender, EventArgs e)
        {
            switch (AnaCBX.SelectedIndex)
            {
                case 0:
                    try
                    {
                        MessageBox.Show(IsAnagram<int>(AnaTB1.Text.Split(' ').Select(int.Parse).ToList(), AnaTB2.Text.Split(' ').Select(int.Parse).ToList()).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }

                case 1:
                    try
                    {
                        MessageBox.Show(IsAnagram(AnaTB1.Text.Split(' ').Select(float.Parse).ToList(), AnaTB2.Text.Split(' ').Select(float.Parse).ToList()).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
                case 2:
                    try
                    {
                        MessageBox.Show(IsAnagram<char>(AnaTB1.Text, AnaTB2.Text).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
                case 3:
                    try
                    {
                        MessageBox.Show(IsAnagram<string>(AnaTB1.Text.Split(' ').ToList(), AnaTB2.Text.Split(' ').ToList()).ToString());
                        break;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message.ToString());
                        break;
                    }
            }
        }
    
    }
}
