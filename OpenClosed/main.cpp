/*
 * Open For extension | Closed for Modification
 */

#include <iostream>
#include <vector>

enum Color { Green, Blue, Red };

enum Type { Battleship, Cruiser, Cargo };

enum Size { Small, Medium, Large };

struct Ship {
    std::string name = "Name";
    Type type = Type::Cargo;
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

struct AdvancedFilter : Filter<Ship> {
    std::vector<Ship *> filter(std::vector<Ship *> items, Specification<Ship> &spec) override {
        std::vector<Ship *> result;
        for (auto &item: items)
            if (spec.is_satisfied(item))
                result.emplace_back(item);
        return result;
    }
};

// --------------------------------------------------------------------------
struct TypeSpecification : Specification<Ship> {
    Type type;
    explicit TypeSpecification(Type type):type(type){}

    bool is_satisfied(Ship *item) const override {
        return item->type == type;
    }
};

struct ColorSpecification : Specification<Ship> {
    Color color;

    explicit ColorSpecification(Color color): color(color) {
    }

    bool is_satisfied(Ship *item) const override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Ship> {
    Size size;

    explicit SizeSpecification(Size size): size(size) {
    }

    bool is_satisfied(Ship *item) const override {
        return item->size == size;
    }
};

// -------------------------------------------------------------
template<typename T>
struct AndSpecification : Specification<T> {
    const Specification<T> &first;
    const Specification<T> &second;

    AndSpecification(const Specification<T> &first, const Specification<T> &second)
        : first(first), second(second) {
    }

    bool is_satisfied(T *item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main() {
    std::cout << "Open/Closed Principle" << std::endl;

    Ship Taunus{"Taunus", Cruiser, Blue, Large};
    Ship AirDrop{"AirDrop", Cargo,Green, Large};
    Ship Thunder{"Thunder", Battleship,Red, Medium};
    Ship Mosquito{"Mosquito", Battleship,Green, Small};
    Ship Skew{"Skew", Battleship,Blue, Small};

    std::vector<Ship *> Ships{&Taunus, &AirDrop,&Thunder, &Mosquito};
    AdvancedFilter bf;
    TypeSpecification cargo(Cargo);
    for(auto &item : bf.filter(Ships,cargo)) {
        std::cout << item->name << " is Cargo" << std::endl;
    }
    ColorSpecification green(Color::Green);
    for (auto &item: bf.filter(Ships, green)) {
        std::cout << item->name << " is green " << std::endl;
    }

    SizeSpecification large(Size::Large);
    for (auto &item: bf.filter(Ships, large)) {
        std::cout << item->name << " is large " << std::endl;
    }

    auto spec = green && large;
    for (auto &item: bf.filter(Ships, spec)) {
        std::cout << item->name << " is Green and Large " << std::endl;
    }

    auto specType = cargo && green;
    for (auto &item: bf.filter(Ships, specType)) {
        std::cout << item->name << " is Cargo and Green " << std::endl;
    }
    return 0;
}
