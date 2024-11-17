package eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty;

import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.CodeMismatchException;
import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.IncorrectDoorCodeException;

public class ThirdPartyDoorObjectAdapter implements eu.jpereira.trainings.designpatterns.structural.adapter.model.Door {
    
    public enum DoorState {
		OPEN, CLOSED;
	}
	public static final String DEFAULT_CODE ="AAAAHHHH";
    private String code = DEFAULT_CODE;
	private DoorState doorState = DoorState.CLOSED;

    /**
	 * Open the door if the code is correct
	 * 
	 * @param code
	 *            the code to open the door
	 * @throws IncorrectDoorCodeException
	 *             if the code is not correct
	 */
	public void open(String code) throws IncorrectDoorCodeException {
        if (code.equals(this.code)) {
            doorState = DoorState.OPEN;
        } else {
            throw new IncorrectDoorCodeException();
        }
    }

	/**
	 * Attempt to close the door
	 */
	public void close() {
        doorState = DoorState.CLOSED;
    }

    /**
	 * Test if the door is open
	 * 
	 * @return
	 */
	public boolean isOpen() {
        if (doorState == DoorState.OPEN) {
            return true;
        } else {
            return false;
        }
    }

    /**
	 * Attempt to change the door code
	 * 
	 * @param oldCode
	 *            The old code
	 * @param newCode
	 *            the new code
	 * @param newCodeConfirmation
	 *            the new code confirmation
	 * @throws IncorrectDoorCodeException
     * @throws CodeMismatchException
	 */
	public void changeCode(String oldCode, String newCode, String newCodeConfirmation) throws IncorrectDoorCodeException, CodeMismatchException {
        if (oldCode.equals(code)) {
            if (newCode.equals(newCodeConfirmation)) {
                this.code = newCode; 
            } else {
                throw new CodeMismatchException();
            }
        } else {
            throw new IncorrectDoorCodeException();
        }
    }

    /**
	 * Test if a given code can open the door
	 * 
	 * @param code
	 *            the code to test
	 * @return true if the code can open the door, false otherwise
	 */
	public boolean testCode(String code) {
        if (code.equals(this.code)) {
            return true;
        } else {
            return false;
        }
    }
}
