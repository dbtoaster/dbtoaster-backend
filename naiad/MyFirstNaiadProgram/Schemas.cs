using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenTesting
{

    // Query19 data
    public struct Query19TLDSS {
    //def canEqual(that:Any) = true
    //def productArity = 4
    //def productElement(i:Int):Any = List[Any](_1,_2,_3,_4)(i)
    //override def equals(o:Any) = { o match { case x:TLDSS => (_1 == x._1 && _2 == x._2 && _3 == x._3 && _4 == x._4) case x:Product => if(this.productArity == x.productArity) (0 to (productArity - 1)).forall(i => x.productElement(i) == this.productElement(i)) else false case _ => false } }
    //override def toString() = "<"+List[Any](_1,_2,_3,_4).mkString(",")+">"
    public Query19TLDSS(long _1, double _2, string _3, string _4)
        {
            this._1 = _1;
            this._2 = _2;
            this._3 = _3;
            this._4 = _4;
        }
        public long _1;
        public double _2;
        public string _3;
        public string _4;

        public override string ToString()
        {
            return _1 + " " + _2 + " " + _3 + " " + _4;
        }
    public override int GetHashCode() {
      int h = 4;
      h = h * 41 + (int)(_1);
      h = h * 41 + (int)(_2);
      h = h * 41 + _3.GetHashCode();
      h = h * 41 + _4.GetHashCode(); 
      return h;
    }
  }
    public struct Query19TLLLLDDDDSSAAASSS {
    //def canEqual(that:Any) = true
    //def productArity = 16
    //def productElement(i:Int):Any = List[Any](_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16)(i)
    //override def equals(o:Any) = { o match { case x:TLLLLDDDDSSAAASSS => (_1 == x._1 && _2 == x._2 && _3 == x._3 && _4 == x._4 && _5 == x._5 && _6 == x._6 && _7 == x._7 && _8 == x._8 && _9 == x._9 && _10 == x._10 && _11 == x._11 && _12 == x._12 && _13 == x._13 && _14 == x._14 && _15 == x._15 && _16 == x._16) case x:Product => if(this.productArity == x.productArity) (0 to (productArity - 1)).forall(i => x.productElement(i) == this.productElement(i)) else false case _ => false } }
    //override def toString() = "<"+List[Any](_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16).mkString(",")+">"
        Query19TLLLLDDDDSSAAASSS(long _1, long _2, long _3, long _4, double _5, double _6, double _7, double _8, string _9, string _10, DateTime _11, DateTime _12, DateTime _13, string _14, string _15, string _16)
        {
            this._1 = -1;
            this._2 = _2;
            this._3 = _3;
            this._4 = _4;
            this._5 = _5;
            this._6 = _6;
            this._7 = _7;
            this._8 = _8;
            this._9 = _9;
            this._10 = _10;
            this._11 = _11;
            this._12 = _12;
            this._13 = _13;
            this._14 = _14;
            this._15 = _15;
            this._16 = _16;
        }
        
        long _1;
        long _2;
        long _3;
        long _4;
        double _5;
        double _6;
        double _7;
        double _8;
        string _9;
        string _10;
        DateTime _11;
        DateTime _12;
        DateTime _13;
        string _14;
        string _15;
        string _16;
    public override int GetHashCode() {
      int h = 16;

      return h;
    }
  }
    public struct Query19TLSLS {
    public Query19TLSLS(long _1, string _2, long _3, string _4) {
        this._1 = _1;
        this._2 = _2;
        this._3 = _3;
        this._4 = _4;
    }

    public long _1; 
    public string _2; 
    public long _3; 
    public string _4;
    public override int GetHashCode() {
      /*int h = 4;
      h = h * 41 + (int)_1;
      h = h * 41 + _2.GetHashCode();
      h = h * 41 + (int)_3;
      h = h * 41 + _4.GetHashCode();
      return h;*/
        return base.GetHashCode();
    }
  }
    public struct Query19TLSSSSLSDS {
      Query19TLSSSSLSDS(long _1, string _2, string _3, string _4, string _5, long _6, string _7, double _8, string _9)
      {
          this._1 = _1;
          this._2 = _2;
          this._3 = _3;
          this._4 = _4;
          this._5 = _5;
          this._6 = _6;
          this._7 = _7;
          this._8 = _8;
          this._9 = _9;

      }
      long _1;
      string _2;
      string _3;
      string _4;
      string _5;
      long _6;
      string _7;
      double _8;
      string _9;
    public int GetHashCode() {
      int h = 9;
      return h;
    }
  }
    public struct LINEITEM {
        public int function;
        public long orderkey;
        public long partkey;
        public long suppkey;
        public long linenumber;
        public double quantity;
        public double extendedprice;
        public double discount;
        public double tax;
        public char returnflag;
        public char linestatus;
        public DateTime shipdate;
        public DateTime commitdate;
        public DateTime receiptdate;
        public string shipinstruct;
        public string shipmode;
        public string comment;

        public override int GetHashCode()
        {
            return (int)linenumber;
        }
    }
    public struct LINEITEM19
    {
        public int function;
        public long orderkey;
        public long partkey;
        public long suppkey;
        public long linenumber;
        public double quantity;
        public double extendedprice;
        public double discount;
        public double tax;
        public char returnflag;
        public char linestatus;
        public DateTime shipdate;
        public DateTime commitdate;
        public DateTime receiptdate;
        public string shipinstruct;
        public string shipmode;
        public string comment;

        public override int GetHashCode()
        {
            return (int)(partkey);
        }
    }
    public struct PART19 {
        public int function;
        public int partkey;
        public string name;
        public string mfgr;
        public string brand;
        public string type;
        public int size;
        public string container;
        public double retailprice;
        public string comment;

        public override int GetHashCode()
        {
            return partkey;
        }

    }

    // Query1 data
    public struct Query1TSS {
        public Query1TSS(char _1, char _2) {
            this._1 = _1;
            this._2 = _2;
        }

        public char _1;
        public char _2;

        public override string ToString()
        {
            return _1 + " " + _2;
        }

    override public int GetHashCode() {
        return (_1 + _2).GetHashCode(); 
    }
  }
    public struct LINEITEM1
    {
        public int function;
        public long orderkey;
        public long partkey;
        public long suppkey;
        public long linenumber;
        public double quantity;
        public double extendedprice;
        public double discount;
        public double tax;
        public char returnflag;
        public char linestatus;
        public DateTime shipdate;
        public DateTime commitdate;
        public DateTime receiptdate;
        public string shipinstruct;
        public string shipmode;
        public string comment;

        public override int GetHashCode()
        {
            return (returnflag + linestatus).GetHashCode();
        }
    }


    // Query 17a
    public struct LINEITEM17a
    {
        public int function;
        public long orderkey;
        public long partkey;
        public long suppkey;
        public long linenumber;
        public double quantity;
        public double extendedprice;
        public double discount;
        public double tax;
        public char returnflag;
        public char linestatus;
        public DateTime shipdate;
        public DateTime commitdate;
        public DateTime receiptdate;
        public string shipinstruct;
        public string shipmode;
        public string comment;

        public override int GetHashCode()
        {
            return (int)(partkey);
        }
    }
    public struct PART17a
    {
        public int function;
        public int partkey;
        public string name;
        public string mfgr;
        public string brand;
        public string type;
        public int size;
        public string container;
        public double retailprice;
        public string comment;

        public override int GetHashCode()
        {
            return partkey;
        }

    }
    public struct TLD17a
    {
        public long _1;
        public double _2;

        public TLD17a(long _1, double _2)
        {
            this._1 = _1;
            this._2 = _2;
        }

        public override int GetHashCode()
        {
            int h = 2;
            h = h * 41 + (int)_1;
            h = h * 41 + (int)_2;

            return h;
        }
    }


    // Query 4
    public struct LINEITEM4
    {
        public int function;
        public long orderkey;
        public long partkey;
        public long suppkey;
        public long linenumber;
        public double quantity;
        public double extendedprice;
        public double discount;
        public double tax;
        public char returnflag;
        public char linestatus;
        public DateTime shipdate;
        public DateTime commitdate;
        public DateTime receiptdate;
        public string shipinstruct;
        public string shipmode;
        public string comment;

    }
    public struct ORDERS4
    {
        public int function;
        public int orderkey;
        public int custkey;
        public char orderstatus;
        public double totalprice;
        public DateTime orderdate;
        public string orderpriority;
        public string clerk;
        public int shippriority;
        public string comment;
    }

    public struct TLS4
    {
        public long _1;
        public string _2;
        
        public TLS4(long _1, string _2)
        {
            this._1 = _1;
            this._2 = _2;
        }
        public override int GetHashCode()
        {
            int h = 2;
            h = h * 41 + (int)_1;
            h = h * 41 + _2.GetHashCode();
            return h;
        }
  
    }
}
