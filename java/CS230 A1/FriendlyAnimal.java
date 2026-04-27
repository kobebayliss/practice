/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Represents a friendly animal that is easy to rescue,
 * using low energy and giving a moderate score reward.
 */

class FriendlyAnimal extends Animal {

    public FriendlyAnimal() {
        super(3, 10);
    }

    public FriendlyAnimal(int x, int y) {
        super(x, y, 3, 10);
    }

    @Override
    public void rescue(Rescuer r) {
        r.decreaseEnergy(this.energy);
        r.addScore(this.score);

        System.out.println(
            "Rescued " + getClass().getSimpleName() +
            " at (" + location.x + ", " + location.y + "): +" +
            score + " score, -" + energy + " energy"
        );
    }
}