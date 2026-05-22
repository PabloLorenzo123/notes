

Producer<Tabaco> Cuba = new Producer<Tabaco>();

Coffee coffe = Cuba.produce();




class Coffee {}

class Tabaco {}

class Producer<T>
{
    public T Produce() => new T();
}
