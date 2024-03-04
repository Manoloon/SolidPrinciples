# SOLID Principles

# Single Responsibility :
- Each function should have only one responsibility : getValue() -> return just the value , no other action inside the function should be done.
# Open-Closed Principle (open for extension,closed for implementation) : 
- The class should be open for extension but closed for implementation , in other words no one should change the class implementation but should extend from it.
# Liskov Substitution : 
- Object of a superClass should be replaceable without breaking the code. Example : Class Circle : public Object could be replaceable with  class Square : public object , circle use radius , square use area. Interfaces played a key role here.
# Interface Segregation : 
- Talking about interfaces, this principle states that the interfaces shouldn't have functions or values that aren't used by all classes involved. If that is so, the interface needs to be segregated into smaller ones.
# Dependency Inversion :
- Logic in High level modules should be reusable and unaffected by changes in low level modules which provide utility. Both depend on the abstraction.
