//ConfigurationSettings_basic.cpp
#include <iostream>
#include <string>

class ConfigurationSettings {
public:
    static ConfigurationSettings& getInstance() {
        static ConfigurationSettings instance;
        return instance;
    }

    std::string getSetting(const std::string& key) {
        // Simulate getting a setting from a configuration file
        if (key == "godOfTheUnderworld") {
            return "Hades";
        }
        return "";
    }

private:
    ConfigurationSettings() {}
};

int main() {
    ConfigurationSettings& settings = ConfigurationSettings::getInstance();
    std::cout << settings.getSetting("godOfTheUnderworld") << std::endl;
    return 0;
}
//ConfigurationSettings_thread_safe.cpp
#include <iostream>
#include <string>
#include <mutex>

class ConfigurationSettings {
public:
    static ConfigurationSettings& getInstance() {
        // Use call_once to ensure the instance is created only once in a thread-safe manner
        std::call_once(initInstanceFlag, createInstance);
        return *instance;
    }

    std::string getSetting(const std::string& key) {
        // Simulate getting a setting from a configuration file
        if (key == "godOfTheUnderworld") {
            return "Hades";
        }
        return "";
    }
    // Declare but do not define copy constructor and assignment operator to prevent copying
    ConfigurationSettings(const ConfigurationSettings&) = delete;
    ConfigurationSettings& operator=(const ConfigurationSettings&) = delete;
private:
    ConfigurationSettings() = default;
    ~ConfigurationSettings() = default;

    static void createInstance() {
        instance = new ConfigurationSettings();
    }

    static ConfigurationSettings* instance;
    static std::once_flag initInstanceFlag;
};

ConfigurationSettings* ConfigurationSettings::instance = nullptr;
std::once_flag ConfigurationSettings::initInstanceFlag;

int main() {
    ConfigurationSettings& settings = ConfigurationSettings::getInstance();
    std::cout << settings.getSetting("godOfTheUnderworld") << std::endl;
    return 0;
}
