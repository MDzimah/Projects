package tp1.control;

import tp1.exceptions.CommandExecuteException;
import tp1.logic.*;
import tp1.view.GameView;
import tp1.view.Messages;

public class HelpCommand extends NoParamsCommand{
	private static final String NAME = Messages.COMMAND_HELP_NAME;
	private static final String SHORTCUT = Messages.COMMAND_HELP_SHORTCUT;
	private static final String DETAILS = Messages.COMMAND_HELP_DETAILS;
	private static final String HELP = Messages.COMMAND_HELP_HELP;
	
	HelpCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}
	
	@Override
	void execute(GameModel g, GameView view) throws CommandExecuteException { 
		view.showMessage(CommandGenerator.commandHelp());
	}
}
