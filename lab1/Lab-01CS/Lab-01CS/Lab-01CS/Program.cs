using System;
class Program
{
    static void CalculatePowers(double x, out double x4, out double x12, out double x28)
    {
        double x2 = x * x;
        x4 = x2 * x2;
        double x8 = x4 * x4;
        x12 = x8 * x4;
        double x16 = x8 * x8;
        x28 = x16 * x12;
    }
static void Main()
    {
        Console.Write("Chislo x: ");
        double x = Convert.ToDouble(Console.ReadLine());

        CalculatePowers(x, out double x4, out double x12, out double x28);
        Console.WriteLine($"x^4 = {x4:F6}");
        Console.WriteLine($"x^12 = {x12:F6}");
        Console.WriteLine($"x^28 = {x28:F6}");

        Console.WriteLine("Нажмите Enter для выхода...");
        Console.ReadLine();
    }
}