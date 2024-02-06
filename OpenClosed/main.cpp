/*
 * Open For extension | Closed for Modification
 */

#include <iostream>
#include <vector>

enum Color { Green, Blue, Red };

enum Size { Small, Medium, Large };

struct Product {
    std::string name = "Name";
    Color color = Color::Blue;
    Size size = Size::Small;
};

template<typename T>
struct AndSpecification;

template<typename T>
struct Specification {
    virtual ~Specification() = default;

    virtual bool is_satisfied(T *item) const =0;
};

template<typename T>
AndSpecification<T> operator&&(const Specification<T> &first, const Specification<T> &second) {
    return {first, second};
}

template<typename T>
struct Filter {
    virtual ~Filter() = default;

    virtual std::vector<T *> filter(std::vector<T *> item, Specification<T> &spec) =0;
};

struct BetterFilter : Filter<Product> {
    std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> &spec) override {
        std::vector<Product *> result;
        for (auto &item: items)
            if (spec.is_satisfied(item))
                result.emplace_back(item);
        return result;
    }
};

// --------------------------------------------------------------------------
struct ColorSpecification : Specification<Product> {
    Color color;

    explicit ColorSpecification(Color color): color(color) {
    }

    bool is_satisfied(Product *item) const override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(Size size): size(size) {
    }

    bool is_satisfied(Product *item) const override {
        return item->size == size;
    }
};

// -------------------------------------------------------------
template <typename T> struct AndSpecification : Specification<T>
{
    const Specification<T>& first;
    const Specification<T>& second;

    AndSpecification(const Specification<T>& first, const Specification<T>& second)
      : first(first), second(second) {}

    bool is_satisfied(T *item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main() {
    std::cout << "Open/Closed Principle" << std::endl;

    Product Ball{"Ball", Color::Blue, Size::Large};
    Product Alien{"Alien", Color::Green, Size::Small};
    Product Tree{"Tree", Color::Green, Size::Large};

    std::vector<Product *> Products{&Ball, &Alien, &Tree};
    BetterFilter bf;
    ColorSpecification green(Color::Green);
    for (auto &item: bf.filter(Products, green)) {
        std::cout << item->name << " is green " << std::endl;
    }

    SizeSpecification large(Size::Large);
    for (auto &item: bf.filter(Products, large)) {
        std::cout << item->name << " is large " << std::endl;
    }

    auto spec = green && large;
    for (auto &item: bf.filter(Products, spec)) {
        std::cout << item->name << " is Green and Large " << std::endl;
    }
    return 0;
}
