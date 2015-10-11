import model.*;
import view.*;
import controller.*;

/**
 * This class runs the game.
 * @author Tomasz Bochenski
 */
public class Game
{
	public static void main(String[] args)
	{
		Model model = new Model();
		View view = new View(model);
		Controller controller = new Controller(model, view);
	}
}
