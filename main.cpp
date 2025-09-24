#include <concepts>
#include <iostream>
#include <type_traits>
#include <string>

template <typename T>
concept ComplexConcept = requires(const T v) {
    { v.hash() } -> std::convertible_to<long>;
    { v.toString() } -> std::same_as<std::string>;
    requires !std::has_virtual_destructor_v<T>;
};

struct Number {
    int _num{0};    

    // Метод hash, возвращающий long (требование convertible_to<long>)
    long hash() const {
        return static_cast<long>(_num) * 31; // Простая хеш-функция
    }

    // Метод toString, возвращающий string (требование same_as<string>)
    std::string toString() const {
        return std::to_string(_num);
    }
};

void PrintType(const ComplexConcept auto &t){
    std::cout << "hash " << t.hash() << '\n';
    std::cout << "string " << t.toString() << '\n';
};

int main() {
    Number x{42};
    PrintType(x);
}