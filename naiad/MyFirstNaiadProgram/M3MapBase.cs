using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenTesting
{
    public abstract class M3Map<K,V>
    {
        public abstract V get(K key);           // returns the value or zero if it is not present
        public abstract void set(K key, V value);    // inserts or set the value
        public abstract void add(K key,V value);    // combines new value with existing one using 'plus'
        public abstract IEnumerable<Entry<K, V>> tempforeach(); // iterates through all non-zero values of the map
        public abstract M3Map<K, V> slice<T>(int index, T subKey); // partition where the secondary index is equal to subKey
        //def sum(acc:M3Map[K,V]);    // accumulate in acc: acc <- element_wise_sum(this,acc)
        public abstract void clear();                // erases all elements of the map or slice
        public abstract int size();               // number of key-value mappings in the map

    }
    public abstract class Plus<T> { public abstract T apply(T a, T b); }
    public class PlusLong : Plus<long> { public override long apply(long a, long b) { return a + b; } }
    public class PlusDouble : Plus<double> { public override double apply(double a, double b) { return a + b; } }
    public class PlusString : Plus<string> { public override string apply(string a, string b) { return a + b; } }
    
    public abstract class Function1<K, P> { public abstract P apply(K t); }
    public class Entry<K, V> : IComparable<Entry<K, V>>
    {
        private readonly int hash;
        public readonly K key;
        public V value;
        public Entry<K, V> next;
        public Entry(int h, K k, V v, Entry<K, V> n)
        {
            hash = h; 
            key = k; 
            value = v; 
            next = n;
        }

        public override bool Equals(object obj)
        {
            Entry<K, V> that = (Entry<K, V>)obj;
            return hash == that.hash && key.Equals(that.key);
        }

        public int CompareTo(Entry<K, V> other)
        {
            if(key is IComparable) 
            {
                return ((IComparable<K>)key).CompareTo(other.key);
            } 
            else 
            {
                return 0;
            }
        }

        public override int GetHashCode()
        {
            return hash;
        }
    }

    // Secondary index storage for slicing. Matching elements are stored in a Hash or a Tree.
    public class Index<K, V, P> 
    {
        private readonly Function1<K, P> proj;        // 1st level (might map all at the same place)
        private readonly IComparer<Entry<K,V>> cmp;   // 2nd level (tree structure)
        private Dictionary<P, HashSet<Entry<K,V>>> data;

        private class EntryComparer<K, V> : IComparer<Entry<K, V>> {
            IComparer<K> c;
            public EntryComparer(IComparer<K> c) {this.c = c;}
            public int Compare(Entry<K,V> e1, Entry<K,V> e2)
            {
                return c.Compare(e1.key,e2.key); 
            }
        }
        public Index(Function1<K,P> projection) : this(projection, null) { }
        public Index(Function1<K,P> projection, IComparer<K> comparator) 
        { 
            proj = projection;
            IComparer<K> c = comparator != null ? comparator : ((projection is IComparer<K>) ? (IComparer<K>)projection : null);
            cmp = c == null ? null : new EntryComparer<K, V>(c);
            data = new Dictionary<P, HashSet<Entry<K,V>>>();
        }
        public void clear() { data.Clear(); }
        public void add(Entry<K,V> e) 
        { 
            P p=proj.apply(e.key); 
            HashSet<Entry<K,V>> s = null;
            if (data.ContainsKey(p)) s = data[p]; 

            if (s==null) 
            { 
                //s=(cmp!=null)?new TreeSet<Entry<K,V>>(cmp):new /*HashSet<Entry<K,V>>*/ HESet<K,V>(); 
                s = new HashSet<Entry<K, V>>();
                data.Add(p,s); 
            } 
            s.Add(e); 
        }
        public void del(Entry<K,V> e) 
        { 
            P p=proj.apply(e.key); 
            HashSet<Entry<K,V>> s= null;
            if(data.ContainsKey(p)) s = data[p]; 
            if (s != null) 
            { 
                s.Remove(e); 
                if (s.Count == 0) 
                    data.Remove(p); //data.remove(s); ????????? is it bug ?
            } 
        }

        public HashSet<Entry<K, V>> slice(Object part) 
        {
            HashSet<Entry<K, V>> s = null;
            if(data.ContainsKey((P)part)) s = data[(P)part]; 
            if (s==null) s=new HashSet<Entry<K,V>>(); 
            return s; 
        }
        /*HashSet<Entry<K, V>> slice(Object part, K low, K high, bool lowIn, bool highIn)
        { // assert(cmp!=null);
            HashSet<Entry<K, V>> s = (TreeSet<Entry<K, V>>)data.get((P)part);
            Entry<K, V> l = new Entry<K, V>(0, low, zero, null);
            Entry<K, V> h = new Entry<K, V>(0, high, zero, null);
            if (s == null) s = new TreeSet<Entry<K, V>>();
            return s.subSet(l, lowIn, h, highIn);
        }*/
    }
    
    public class M3MapBase<K, V>
    {
        private static readonly int INITIAL_CAPACITY = 1024;
        private static readonly int MAXIMUM_CAPACITY = 1 << 30;
        private static readonly float LOAD_FACTOR = 0.75f;
        private Entry<K,V>[] data;
        private int map_size;
        private int threshold;
        private readonly V zero;
        private readonly Plus<V> plus; // inferred from zero
        private readonly bool skipZero = false;
        private readonly Index<K, V, object>[] indices;

        public M3MapBase() : this(default(V), false, null) { }
        public M3MapBase(V zero, bool skipZero, Function1<K, object>[] projections) 
        {
            threshold = (int)(INITIAL_CAPACITY * LOAD_FACTOR);
            data = new Entry<K, V>[INITIAL_CAPACITY];
            this.zero = zero; 
            this.skipZero = skipZero;
            if (projections==null) indices = null;
            else 
            {
                //indices = (Index<?>[])java.lang.reflect.Array.newInstance(Index.class, projections.length);
                indices = new Index<K, V, object>[projections.Length];
                for(int i = 0; i < projections.Length; ++i) 
                    indices[i] = new Index<K, V, Object>(projections[i], null);
            }
           
            if (zero is long) plus = (Plus<V>)(new PlusLong() as object);
            else if (zero is double) plus = (Plus<V>) (new PlusDouble() as object);
            else if (zero is String) plus = (Plus<V>) (new PlusString() as object);
            //else if (zero is Date) plus = (Plus<V>) new Plus<Date>() { Date apply(Date a, Date b) { return new Date(a.getTime()+b.getTime()); } };
            else plus=null;
        }
        //protected V zero() { return zero; } // exposed for Akka (accumulator for partial aggregations)
        private static int hash(Object k) 
        { 
            uint h = (uint)k.GetHashCode(); 
            h^=(h>>20)^(h>>12)^(h<<9); 
            return (int)(h^(h>>7)^(h>>4)); 
            //return k.GetHashCode();
        }
        private static int indexFor(int h, int length) { return h & (length-1); }
        public Entry<K,V> find(K key) 
        {
            int h = hash(key); 
            int b = indexFor(h, data.Length); 
            Entry<K,V> e = data[b];
            if (e!=null) 
                do 
                {
                    //Console.WriteLine(h + " " + e.GetHashCode());
                    //Console.WriteLine(key + " " + e.key);
                    if ( h == e.GetHashCode() && key.Equals(e.key)) 
                        return e; 
                } while ((e = e.next)!=null); 
            
            return null;
        }
  
        private void resize(int newCapacity) 
        { 
            if (data.Length == MAXIMUM_CAPACITY) 
            { 
                threshold = Int32.MaxValue; 
                return; 
            }
            Entry<K, V>[] newData=new Entry<K, V>[newCapacity]; 
            Entry<K,V> next=null;
            foreach (Entry<K,V> tmp in data) 
            {
                Entry<K, V> e = tmp;
                if (e!=null) do { 
                    next=e.next; 
                    int b=indexFor(e.GetHashCode(), newCapacity); 
                    e.next=newData[b]; 
                    newData[b]=e; 
                } while((e=next)!=null);
            }
            data = newData; 
            threshold=(int)Math.Min(newCapacity * LOAD_FACTOR, MAXIMUM_CAPACITY + 1);
        }
        
        private void createEntry(int hash, K key, V value, int bucketIndex) 
        {
            Entry<K,V> e = new Entry<K,V>(hash, key, value, data[bucketIndex]); 
            data[bucketIndex]=e; 
            ++map_size;
            if (indices!=null) 
            { 
                foreach (Index<K, V, Object> i in indices) i.add(e); 
            }
        }
        
        private void putNoResize(K key, V value) 
        {
            int h=hash(key); 
            int i=indexFor(h,data.Length);
            for (Entry<K,V> e=data[i]; e!=null; e=e.next) 
                if (h==e.GetHashCode() && key.Equals(e.key)) 
                { 
                    e.value = value; 
                    return; 
                }
            createEntry(h, key, value, i);
        }
        // Minimal conventional Map interface
        public int size() 
        { 
            return map_size; 
        }
        public void put(K key, V value) 
        {
            int h = hash(key); 
            int b = indexFor(h, data.Length);
            for(Entry<K,V> e=data[b];e!=null;e=e.next) 
                if (h==e.GetHashCode() && key.Equals(e.key)) 
                { 
                    e.value=value; 
                    return; 
                }
            if ((map_size >= threshold) && (data[b]!=null)) 
            { 
                resize(2*data.Length); 
                b=indexFor(h,data.Length); 
            }
            createEntry(h,key,value,b);
        }
        public V remove(K key) 
        {
            int h=hash(key); 
            int b=indexFor(h, data.Length);
            Entry<K,V> prev=data[b],e=prev;
            while (e!=null) 
            {
                Entry<K,V> next=e.next;
                if (h==e.GetHashCode() && key.Equals(e.key)) 
                {
                    if (prev==e) data[b]=next; 
                    else prev.next=next; 
                    map_size--;
                    if (indices!=null) 
                    { 
                        foreach (Index<K, V, Object> i in indices) 
                            i.del(e); 
                    }
                    return e.value;
                }
                prev=e; e=next;
            }
            return default(V);
        }
        
        // M3Map interface
        public V get(K key) 
        { 
            Entry<K,V> e=find(key); 
            return e==null ? zero : e.value; 
        }
        public void set(K key, V value) 
        { 
            if (skipZero && value.Equals(zero)) 
                remove(key);
            else put(key,value); 
        }
        
        public void add(K key, V value) 
        { 
            if (skipZero && value.Equals(zero)) 
                return; 
            Entry<K,V> e=find(key);
            if (e==null) put(key,value); 
            else 
            { 
                e.value=plus.apply(e.value,value); 
                if (skipZero && e.value.Equals(zero)) remove(key); 
            }
        }
        
        public M3Map<K,V> slice<T>(int index, T subKey) 
        { 
            return new Slice<K, V>(indices[index].slice(subKey), this); 
        }
        
        public void sum(M3Map<K,V> acc) 
        { 
            foreach (Entry<K,V> tmp in data) 
            {
                Entry<K, V> e = tmp;
                for(;e!=null;e=e.next) 
                    acc.add(e.key,e.value); 
            }
        }
        
        public void clear() 
        { 
            for (int i=0;i<data.Length;++i) 
                data[i]=null; 
            
            map_size=0; 
            if (indices!=null) 
                foreach(Index<K, V, Object> i in indices) 
                { 
                    i.clear(); 
                } 
        }

        public IEnumerable<Entry<K, V>> tempforeach()
        {
            HashSet<Entry<K, V>> copyData = new HashSet<Entry<K, V>>();
            foreach (Entry<K, V> tmp in data)
            {
                Entry<K, V> e = tmp;
                for (; e != null; e = e.next)
                    copyData.Add(e);
            }
            return copyData;
        }
    }

    // A slice behaves mostly like the original map but only on 1 of its partition.
    public class Slice<K, V> : M3Map<K,V> {
        private readonly HashSet<Entry<K,V>> data;
        private M3MapBase<K, V> map;
        public Slice(HashSet<Entry<K,V>> set, M3MapBase<K, V> map) { data = set; this.map = map;}

        // Faked operations (to be better implemented)
        public override void set(K key, V value) { map.set(key,value); }
        public override void add(K key, V value) { map.add(key,value); }
        public override M3Map<K,V> slice<T>(int index, T subKey) { return this; }
        



        // Slice-specific operations
        public override V get(K key) 
        { 
            Entry<K,V> e= map.find(key); 
            if (e!=null && !data.Contains(e)) 
                e=null; 
 
            return e!=null ? e.value : default(V); 
        }
        public override int size() { return data.Count(); }
        public override void clear() { foreach(Entry<K,V> e in data) map.remove(e.key); }
        public override IEnumerable<Entry<K, V>> tempforeach()
        {
            return data;
        }

        public void sum(M3Map<K,V> acc) { foreach(Entry<K,V> e in data) acc.add(e.key,e.value); }
    }
}
