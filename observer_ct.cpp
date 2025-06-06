#include <cstdint>
#include <cstdio>
#include <functional>
#include <vector>

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

template<typename T>
concept Updatable = requires (T, float f) {
    { T::update(f) } -> std::same_as<void>; 
};

template<typename T>
concept Notifiable = requires (T, float f) {
    { T::notify(f) } -> std::same_as<void>; 
};

template <typename... Subs>
struct publisher {
    static void notify(float temp) {
        (call_update_or_notify<Subs>(temp), ...);
    }
private:
    template<typename T>
    static void call_update_or_notify(float temp) {
        if constexpr (Updatable<T>) {
            T::update(temp);
        } else if constexpr (Notifiable<T>) {
            T::notify(temp);
        }
        else {
            static_assert(false, "Type is not Updatable or Notifiable");
        }
    }
};

int main() {
    using temp_publisher = publisher<display, data_sender>;
    temp_publisher::notify(23.47);
    using temp_publisher_new = publisher<temp_publisher, logger>;
    temp_publisher_new::notify(42.42);
    while(true)
    {
    }
}
