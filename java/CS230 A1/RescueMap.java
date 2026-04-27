/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Manages a collection of animals and coordinates the rescue
 * process by selecting the nearest animal for the rescuer to save.
 */

import java.util.ArrayList;

class RescueMap {

    private ArrayList<Animal> animals;
    private Rescuer rescuer;

    public RescueMap(Rescuer rescuer) {
        animals = new ArrayList<>();
        this.rescuer = rescuer;
    }

    public void addAnimal(Animal a) {
        animals.add(a);
    }

    public int getNumberOfAnimals() {
        return animals.size();
    }

    public ArrayList<Animal> getAnimals() {
        return new ArrayList<>(animals);
    }

    private Animal findNearestAnimal() {
        double smallest = Double.POSITIVE_INFINITY;
        Animal closestAnimal = null;

        for (Animal animal : animals) {
            double distance = rescuer.getDistance(animal); // avoid recomputing
            if (distance < smallest) {
                smallest = distance;
                closestAnimal = animal;
            }
        }

        return closestAnimal;
    }

    public void startRescue() {
        while (!animals.isEmpty() && rescuer.getEnergy() > 0) {
            Animal next = findNearestAnimal();

            if (next == null) {
                break; // safety check (shouldn't normally happen)
            }

            if (rescuer.getEnergy() < next.getEnergy()) {
                System.out.println(
                    "Not enough energy to rescue " +
                    next.getClass().getSimpleName() +
                    ". Required: " + next.getEnergy() +
                    ", Available: " + rescuer.getEnergy()
                );
                break;
            }

            rescuer.rescueAnimal(next);
            animals.remove(next);

            System.out.println(
                "Current Status -> Energy: " +
                rescuer.getEnergy() +
                ", Score: " +
                rescuer.getScore()
            );
        }

        System.out.println("Rescue finished!");
        System.out.println(rescuer);
    }
}