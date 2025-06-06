#include <cstdint>
#include <cstdio>
#include <functional>

struct display {
    static void update(float temp) {
        printf("Displaying temperature %.2f \r\n", temp);
    }
};

struct data_sender {
    static void update(float temp) {
        printf("Sending temperature %.2f \r\n", temp);
    }
};

struct logger {
    static void update(float temp) {
        printf("Logging temperature %.2f \r\n", temp);
    }
};

template <typename... Subs>
struct publisher {
    static void notify(float temp) {
        (Subs::update(temp), ...);
    }
};

int main() {
    using temp_publisher = publisher<display, data_sender, logger>;
    temp_publisher::notify(23.47);
    while(true)
    {
    }
}
