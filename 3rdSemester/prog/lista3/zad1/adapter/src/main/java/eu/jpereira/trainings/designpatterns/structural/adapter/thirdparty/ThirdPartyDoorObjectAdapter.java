package eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty;

import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.CodeMismatchException;
import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.IncorrectDoorCodeException;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeCodeForUnlockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeStateOfLockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotUnlockDoorException;

import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.ThirdPartyDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.ThirdPartyDoor.DoorState;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.ThirdPartyDoor.LockStatus;

public class ThirdPartyDoorObjectAdapter implements eu.jpereira.trainings.designpatterns.structural.adapter.model.Door {
    
	ThirdPartyDoor door = new ThirdPartyDoor();

    /**
	 * Open the door if the code is correct
	 * 
	 * @param code
	 *            the code to open the door
	 * @throws IncorrectDoorCodeException
	 *             if the code is not correct
	 */
	public void open(String code) throws IncorrectDoorCodeException {
        try {
			door.unlock(code);
			door.setState(DoorState.OPEN);
		} catch (CannotUnlockDoorException | CannotChangeStateOfLockedDoor e) {
			throw new IncorrectDoorCodeException();
		}
    }

	/**
	 * Attempt to close the door
	 */
	public void close() {
		try {
			door.setState(DoorState.CLOSED);
		} catch (CannotChangeStateOfLockedDoor e) {

		}
		door.lock();
    }

    /**
	 * Test if the door is open
	 * 
	 * @return
	 */
	public boolean isOpen() {
        if (door.getState().equals(DoorState.OPEN)) {
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
        try {
			door.unlock(oldCode);
            if (newCode.equals(newCodeConfirmation)) {
                door.setNewLockCode(newCode);
            } else {
                throw new CodeMismatchException();
            }
        } catch (CannotUnlockDoorException | CannotChangeCodeForUnlockedDoor e) {
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
		if (door.getLockStatus().equals(LockStatus.LOCKED)) {
			try {
				door.unlock(code);
				door.lock();
				return true;
			} catch (CannotUnlockDoorException e) {
				return false;
			}
		} else {
			try {
				door.unlock(code);
				return true;
			} catch (CannotUnlockDoorException e) {
				return false;
			}
		}
	}
}
