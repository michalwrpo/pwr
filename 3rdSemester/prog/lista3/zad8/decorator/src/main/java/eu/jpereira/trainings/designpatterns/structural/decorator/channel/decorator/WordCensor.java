package eu.jpereira.trainings.designpatterns.structural.decorator.channel.decorator;

import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannel;

public class WordCensor extends SocialChannelDecorator {

    @Override
    public void deliverMessage(String message) {
        if (delegate != null) {
            delegate.deliverMessage(censor(message));
        }
    }
    
    /**
     * Censor some words in messages
     * 
     * @param message to be censored
     * @return censored message
     */
    public String censor(String message) {
        // Replace these 3 bad words with stars, (?i) makes it ignore case
        message = message.replaceAll("(?i)Microsoft", "***");
        message = message.replaceAll("(?i)Apple", "***");        
        message = message.replaceAll("(?i)Java", "****");
        return message;
    }
}