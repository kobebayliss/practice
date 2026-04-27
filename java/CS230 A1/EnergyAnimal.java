/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Represents an animal that restores energy when rescued,
 * giving no score but increasing the rescuer's energy.
 */

class EnergyAnimal extends Animal {

    public EnergyAnimal() {
        super(10, 0);
    }

    public EnergyAnimal(int x, int y) {
        super(x, y, 10, 0);
    }

    @Override
    public void rescue(Rescuer r) {
        r.increaseEnergy(energy);

        System.out.println(
            "Rescued " + getClass().getSimpleName() +
            " at (" + location.x + ", " + location.y + "): +" +
            energy + " energy"
        );
    }
}