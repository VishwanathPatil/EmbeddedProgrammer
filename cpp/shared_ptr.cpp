#include <iostream>
#include <memory>

void shared_ptr_example() {
    std::shared_ptr<int> sp1 = std::make_shared<int>(20); // Creates a shared_ptr
    std::cout << "sp1 value: " << *sp1 << ", use count: " << sp1.use_count() << std::endl;

    std::shared_ptr<int> sp2 = sp1; // Copies the shared_ptr, increments use count
    std::cout << "After copying sp1 to sp2:\n";
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use count: " << sp2.use_count() << std::endl;

    std::shared_ptr<int> sp3 = std::move(sp2); // Moves ownership to sp3, keeps use count
    std::cout << "After moving sp2 to sp3 use count remains same sp2 becomes null:\n";
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 is now nullptr: " << (sp2 == nullptr ? "true":"false") << std::endl;
    std::cout << "sp3 use count: " << sp3.use_count() << std::endl;
}

int main() {
    shared_ptr_example();
    return 0;
}

