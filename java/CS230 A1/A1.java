/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Main program that runs the rescue simulation by creating
 * a rescuer, generating animals, and executing the rescue process.
 */

import java.util.Scanner;

public class A1 {

    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        System.out.println("Enter rescuer's starting energy (default 10):");
        int energy = input.nextInt();

        if (energy <= 0) {
            System.out.println("Invalid input! Using default energy: 10");
            energy = 10;
        }

        Rescuer rescuer = new Rescuer(energy);
        RescueMap map = new RescueMap(rescuer);

        System.out.println("Enter the number of animals (default 3):");
        int n = input.nextInt();

        if (n <= 0) {
            System.out.println("Invalid input! Using default number of animals: 3");
            n = 3;
        }

        for (int i = 0; i < n; i++) {
            System.out.println("Enter coordinates for animal (x y):");
            int x = input.nextInt();
            int y = input.nextInt();

            Animal animal;

            if ((x + y) % 3 == 0) {
                animal = new AggressiveAnimal(x, y);
            } else if ((x + y) % 2 == 0) {
                animal = new EnergyAnimal(x, y);
            } else {
                animal = new FriendlyAnimal(x, y);
            }

            map.addAnimal(animal);

            System.out.println(
                "Created: " +
                animal.getClass().getSimpleName() +
                " at (" + x + ", " + y + ")"
            );
        }

        System.out.println("\nStarting rescue operation...");
        map.startRescue();

        input.close();
    }
}