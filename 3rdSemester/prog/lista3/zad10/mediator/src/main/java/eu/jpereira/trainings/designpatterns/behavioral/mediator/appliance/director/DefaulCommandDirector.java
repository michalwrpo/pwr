/**
 * Copyright 2011 Joao Miguel Pereira
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
package eu.jpereira.trainings.designpatterns.behavioral.mediator.appliance.director;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import eu.jpereira.trainings.designpatterns.behavioral.mediator.command.Command;
import eu.jpereira.trainings.designpatterns.behavioral.mediator.command.CouldNotExecuteCommandException;
import eu.jpereira.trainings.designpatterns.behavioral.mediator.command.CouldNotRollbackCommandException;
import eu.jpereira.trainings.designpatterns.behavioral.mediator.command.UndoableCommand;


public class DefaulCommandDirector implements CommandDirector{

	// Fail Strategy. It will define how the DirectorrWill fail. Should it try to recover, ignore, fail-fast? 
	protected FailStategy failStrategy = null;
	//The commands to be executed by this director
	protected List<Command> commands = null;
	//Stack maintaining the commands already executed. Used for rollback operations
	private Stack<Command> executedCommands;
    // Map to commands to execute in case of exception
    private Map<Class<? extends Throwable>, List<Command>> exceptionCommandsMap;

	/**
	 * Create new DefaultCommandDirector
	 */
	public DefaulCommandDirector() {
		// Use DEFAULT. Will do a rollback after a first command execution failure
		this.failStrategy = FailStategy.DEFAULT;
		// Delegate instantiation to a factory method
		this.commands = createCommands();
		// Delegate instantiation to a factory method
		this.executedCommands = createExecutedStack();
		// Initialize exceptionCommandsMap
		this.exceptionCommandsMap = new HashMap<>();
	}

	/**
	 * sets the fail strategy
	 * 
	 * @param strategy to be set
	 */
	@Override
	public void setFailStrategy(FailStategy strategy) {
		this.failStrategy = strategy;
	}


	/**
	 * Run commmands
	 * 
	 * @throws ErrorDirectingCommandsException if any command fails
	 */
	@Override
	public void run() throws ErrorDirectingCommandsException {
		for (Command command : this.commands) {

			try {
			    //Push the command to the stack of executed commands
				executedCommands.push(command);
				command.execute();
			} catch (CouldNotExecuteCommandException e) {
				// Default strategy is to rollback
				if (this.failStrategy == FailStategy.DEFAULT) {
					rollback();
				}
				// Log
				e.printStackTrace();
				// try to handle the exception
				handleException(e);
				// abstract
				throw new ErrorDirectingCommandsException(e.fillInStackTrace());
			}
		}
	}

	
	/**
	 * adds commands to be executed
	 * 
	 * @param commands to be executed
	 */
	@Override
	public void addCommand(Command command, Command... commands) {
		// add the command to the array
		this.commands.add(command);
		//Add the Commands in the Array of argument commands to the list of commands to execute
		if (commands != null && commands.length > 0) {
			this.commands.addAll(Arrays.asList(commands));
		}
	}
	
	/**
	 * Rollback the command execution
	 */
	private void rollback() {
		while (!executedCommands.isEmpty()) {
			//Pop the last executed command....
			Command rollBackcommand = executedCommands.pop();
			if (rollBackcommand instanceof UndoableCommand) {
				try {
					//Rollback it
					((UndoableCommand) rollBackcommand).rollback();
				} catch (CouldNotRollbackCommandException e) {
					// Ignore
					e.printStackTrace();
				}
			}
		}
	}
	/**
	 * Factory Method
	 * 
	 * @return
	 */
	protected Stack<Command> createExecutedStack() {
		return new Stack<Command>();
	}

	/**
	 * Factory method
	 * 
	 * @return
	 */
	protected List<Command> createCommands() {
		return new ArrayList<Command>();
	}

    /**
     * Add coomands for handling exceptions.
     * 
     * @param exceptionClass The exception class type.
     * @param commands The commands to execute when this exception is thrown.
     */
    public void addExceptionCommands(Class<? extends Throwable> exceptionClass, Command... commands) {
        // If no commands are provided, do nothing
        if (commands == null || commands.length == 0) {
            return;
        }
        
        // Add the list of commands for the specific exception class
        List<Command> commandList = exceptionCommandsMap.getOrDefault(exceptionClass, new ArrayList<>());
        commandList.addAll(Arrays.asList(commands));
        exceptionCommandsMap.put(exceptionClass, commandList);
    }

    /**
     * Handle exceptions by attempting to execute recovery commands for the given exception type.
     * 
     * @param exception The exception thrown during command execution.
     */
    private void handleException(CouldNotExecuteCommandException exception) {
        List<Command> recoveryCommands = exceptionCommandsMap.get(exception.getClass());
        
        if (recoveryCommands != null && !recoveryCommands.isEmpty()) {
            // Execute recovery commands if they exist for this exception
            for (Command recoveryCommand : recoveryCommands) {
                try {
                    recoveryCommand.execute();
                } catch (CouldNotExecuteCommandException e) {
                    // Log recovery failure (could be extended with a better logging mechanism)
                    e.printStackTrace();
                }
            }
        } else {
            // If no recovery commands found
            System.err.println("No recovery commands available for the exception: " + exception.getClass().getName());
        }
    }
}
