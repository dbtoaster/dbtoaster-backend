package ddbt.lib.store2;
import scala.Function1;
import scala.runtime.BoxedUnit;

/* Removes all the specialization boiler plate to define a Scala function. */
abstract class JFun1<T,R> implements Function1<T,R> {
  // public R apply(T a) { return null; }
  @Override public <A> Function1<T,A> andThen(Function1<R,A> f2) { return null; }
  @Override public <A> Function1<A,R> compose(Function1<A,T> f2) { return null; }

   public void apply$mcVJ$sp(long a) {}
   public long apply$mcJJ$sp(long a) { return 0; }
   public int apply$mcIJ$sp(long a) { return 0; }
   public float apply$mcFJ$sp(long a) { return 0; }
   public double apply$mcDJ$sp(long a) { return 0; }
   public boolean apply$mcZJ$sp(long a) { return false; }

   public void apply$mcVI$sp(int a) {}
   public long apply$mcJI$sp(int a) { return 0; }
   public int apply$mcII$sp(int a) { return 0; }
   public float apply$mcFI$sp(int a) { return 0; }
   public double apply$mcDI$sp(int a) { return 0; }
   public boolean apply$mcZI$sp(int a) { return false; }

   public void apply$mcVF$sp(float a) {}
   public long apply$mcJF$sp(float a) { return 0; }
   public int apply$mcIF$sp(float a) { return 0; }
   public float apply$mcFF$sp(float a) { return 0; }
   public double apply$mcDF$sp(float a) { return 0; }
   public boolean apply$mcZF$sp(float a) { return false; }

   public void apply$mcVD$sp(double a) {}
   public long apply$mcJD$sp(double a) { return 0; }
   public int apply$mcID$sp(double a) { return 0; }
   public float apply$mcFD$sp(double a) { return 0; }
   public double apply$mcDD$sp(double a) { return 0; }
   public boolean apply$mcZD$sp(double a) { return false; }

   public <A> Function1<Object,A> andThen$mcVJ$sp(Function1<BoxedUnit,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcJJ$sp(Function1<Object,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcIJ$sp(Function1<Object,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcFJ$sp(Function1<Object,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcDJ$sp(Function1<Object,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcZJ$sp(Function1<Object,A> f2) { return null; }

   public <A> Function1<Object,A> andThen$mcVI$sp(Function1<BoxedUnit,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcJI$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcII$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcFI$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcDI$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcZI$sp(Function1<Object,A> f2) { return null; };

   public <A> Function1<Object,A> andThen$mcVF$sp(Function1<BoxedUnit,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcJF$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcIF$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcFF$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcDF$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcZF$sp(Function1<Object,A> f2) { return null; };

   public <A> Function1<Object,A> andThen$mcVD$sp(Function1<BoxedUnit,A> f2) { return null; }
   public <A> Function1<Object,A> andThen$mcJD$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcID$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcFD$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcDD$sp(Function1<Object,A> f2) { return null; };
   public <A> Function1<Object,A> andThen$mcZD$sp(Function1<Object,A> f2) { return null; };

   public <A> Function1<A,BoxedUnit> compose$mcVJ$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcJJ$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcIJ$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcFJ$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcDJ$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcZJ$sp(scala.Function1<A,Object> f2) { return null; }

   public <A> Function1<A,BoxedUnit> compose$mcVI$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcJI$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcII$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcFI$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcDI$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcZI$sp(scala.Function1<A,Object> f2) { return null; }

   public <A> Function1<A,BoxedUnit> compose$mcVF$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcJF$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcIF$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcFF$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcDF$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcZF$sp(scala.Function1<A,Object> f2) { return null; }

   public <A> Function1<A,BoxedUnit> compose$mcVD$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcJD$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcID$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcFD$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcDD$sp(scala.Function1<A,Object> f2) { return null; }
   public <A> Function1<A,Object> compose$mcZD$sp(scala.Function1<A,Object> f2) { return null; }
}
