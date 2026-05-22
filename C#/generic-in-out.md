`in` means that the generic is treated as a **Contravariant**, `out` as a **Covariant**, the default is **Invariant**.

# Covariant
In Physics mean two variables change in the same direction. meaning if the variables have a linear relationship.

In Computer Science OOP, Covariant means a more specific type can be used in place of a more general type.
e.g
```
public record Animal(string name);

public record Bird(string name): Animal(name);
```

if we have this:

```
public class Program {
    public static void Main(string[] args){
        var blueBird = new Bird("blue-bird");
        PrintName(blueBird);
    }

    private static void PrintName(Animal animal){
        Console.WriteLine(animal.name);
    }
}
```

this will work, because a Bird can be used as an Animal, and it's obvious, there's nothing in the inferface Animal offers that Bird won't show. This is a covariance.

in a generic type, when the generic parameter is preceded by the `out` keyword, in practice means that the class will offer some members that will return this same generic type.

```
public interface IProccessor<out TProduct, TOrder> 
    where TProduct : Product where TOrder : Order
{
    TProduct Proccess(TOrder order);
}
```

Here IProcessor will produce the Proccess 'Product' or anything that inherits from 'Product'.

# Contravariant
In Physics mean that two variables are proportionally inversed.