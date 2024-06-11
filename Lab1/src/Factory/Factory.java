package Factory;

import Commands.Command;

import java.io.File;
import java.io.FileReader;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;


public class Factory {
    public static Factory getInstance() {
        return f;
    }
    public void initCommandNames() {
        InputStream in = Factory.class.getClassLoader().getResourceAsStream("operands.properties");
        Properties properties = new Properties();

        try {
            properties.load(in);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        }

        for(String key : properties.stringPropertyNames()) {
            commandNames.put(key, properties.getProperty(key));
        }
    }
    public Command createCommand(String commandName) {
        if(!commandNames.containsKey(commandName)) {
            throw new RuntimeException(commandName + " is not registered");
        }

        Command command = null;
        String commandClassName = commandNames.get(commandName);
        try {
            command = (Command) Class.forName("Commands." + commandClassName).getDeclaredConstructor().newInstance();
        } catch(Exception ex) {
            System.out.println(ex.getMessage());
        }
        return command;
    }
    public boolean isRegistered(String key) {
        return commandNames.containsKey(key);
    }
    private Factory() {
        initCommandNames();
    }
    private static final Factory f = new Factory();
    private final HashMap<String, String> commandNames = new HashMap<>();
}


