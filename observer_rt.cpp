#include <cstdint>
#include <cstdio>
#include <functional>
#include <vector>

class subscriber {
public:
    virtual void update(float) = 0;
};

class display : public subscriber {
public:
    void update(float temp) override {
        printf("Displaying temperature %.2f \r\n", temp);
    }
};

class data_sender : public subscriber {
public:
    void update(float temp) override {
        printf("Sending temperature %.2f \r\n", temp);
    }
};

class logger : public subscriber {
public:
    void update(float temp) override {
        printf("Logging temperature %.2f \r\n", temp);
    }
};

class publisher {
public:
    void register_sub(subscriber * sub) {
        if(std::find(subs_.begin(), subs_.end(), sub) == subs_.end()) {
            subs_.push_back(sub);
        }
    }
    void unregister(subscriber * sub) {
        if(auto it = std::find(subs_.begin(), subs_.end(), sub); it != subs_.end()) {
            subs_.erase(it);
        }
    }
    void notify(float value) {
        for(auto sub: subs_) {
            sub->update(value);
        }
    }
private:
    std::vector<subscriber*, 8> subs_;
};

int main()
{
    logger temp_logger;
    display temp_display;
    data_sender temp_data_sender;
    publisher temp_publisher;
    temp_publisher.register_sub(&temp_logger);
    temp_publisher.register_sub(&temp_display);
    temp_publisher.notify(24.02f);
    temp_publisher.unregister(&temp_logger);
    temp_publisher.register_sub(&temp_data_sender);
    temp_publisher.notify(44.02f);
    while(true)
    {
    }
}
