/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Represents an aggressive animal that requires high energy
 * to rescue but gives a high score reward.
 */

class AggressiveAnimal extends Animal {

    public AggressiveAnimal() {
        super(12, 30);
    }

    public AggressiveAnimal(int x, int y) {
        super(x, y, 12, 30);
    }

    @Override
    public void rescue(Rescuer r) {
        r.decreaseEnergy(energy);
        r.addScore(score);

        System.out.println(
            "Rescued " + getClass().getSimpleName() +
            " at (" + location.x + ", " + location.y + "): +" +
            score + " score, -" + energy + " energy"
        );
    }
}