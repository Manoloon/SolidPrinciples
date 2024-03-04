# SOLID Principles

# Single Responsability :
- Each function should have only one responsibility : getValue() -> return just the value , no other action inside the function should be done.
# Open-Closed Principle (open for extension,closed for implementation) : 
- The class should be open for extension but close for implementation , in other words no one should change the class implementation but should extend from it.
# Liskov Substitution : 
- Object of a superClass should be replaceable without breaking the code. Example : Class Circle : public Object could be replaceable with  class Square : public object , circle use radius , square use area. Interfaces played a key role here.
# Interface Segregation : 
- Talking about interfaces, this principle state that the interfaces shouldnt have functions or values that arent used by all classes involve. If that so , the interface need to be segregate into smallers ones.
# Dependency Inversion :
- Logic in High level modules should be rehusable and unaffected by changes in low level modules which provide utility. Both depends on the abstraction.
