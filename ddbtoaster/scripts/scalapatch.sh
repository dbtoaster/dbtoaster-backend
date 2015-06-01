#!/bin/sh
# Source: https://github.com/magarciaEPFL/scala/commit/39007f1d51affb9b56b4d4347ada26574b49960b
#
# Alternative: http://magarciaepfl.github.io/scala/
# > git clone https://github.com/magarciaEPFL/scala.git
# > cd scala
# > git checkout -b GenRefactored99sZ origin/GenRefactored99sZ
# > ant all.clean && ant

# Scala search paths (you can pass it as argument)
SCALA_PATHS="/Developer/Scala /usr/local/scala $1"

if [ ! "$SCALA_HOME" ]; then for f in $SCALA_PATHS; do if [ -d "$f" ]; then SCALA_HOME="$f"; fi done; fi
if [ ! "$SCALA_HOME" -o ! -f "$SCALA_HOME/lib/scala-compiler.jar" ]; then echo "Scala home not found, please pass it as argument"; exit 1; fi
JAR="$SCALA_HOME/lib/scala-compiler.jar"; if [ ! -f "$JAR.backup" ]; then cp "$JAR" "$JAR.backup"; fi
cd `dirname $0`; cd ..; BASE=`pwd`; mkdir -p tmp; cd tmp

printf 'ScalacInline:'
printf ' download'
curl -o Inliners.scala https://raw.github.com/scala/scala/2.10.x/src/compiler/scala/tools/nsc/backend/opt/Inliners.scala 2>/dev/null
patch -p0>/dev/null<<EOF
--- Inliners.scala	2014-03-01 17:37:54.000000000 +0100
+++ Inliners.scala	2014-03-01 17:39:44.000000000 +0100
@@ -409,15 +409,6 @@
           || receiver.isEffectivelyFinal
         )

-        def isApply     = concreteMethod.name == nme.apply
-
-        def isCountable = !(
-             isClosureClass(receiver)
-          || isApply
-          || isMonadicMethod(concreteMethod)
-          || receiver.enclosingPackage == definitions.RuntimePackage
-        )   // only count non-closures
-
         debuglog("Treating " + i
               + "\n\treceiver: " + receiver
               + "\n\ticodes.available: " + isAvailable
@@ -454,6 +445,21 @@
             }
             isSafe && {
                retry   = true
+               /* count only callees other than:
+                *  (a) methods owned by anon-closure-classes;
+                *  (b) @inline-marked methods;
+                *  (c) \`foreach\`, \`filter\`, \`withFilter\`, \`map\`, \`flatMap\`;
+                *  (d) those in RuntimePackage;
+                *  (e) apply methods
+                */
+               val isCountable = !(
+                    isClosureClass(receiver)
+                 || hasInline(concreteMethod)
+                 || hasInline(inc.sym)
+                 || isMonadicMethod(concreteMethod)
+                 || (receiver.enclosingPackage == definitions.RuntimePackage)
+                 || (concreteMethod.name == nme.apply)
+               )
                if (isCountable) count += 1
                pair.doInline(bb, i)
                if (!pair.isInlineForced || inc.isMonadic) caller.inlinedCalls += 1
EOF
printf ' compile'
"$SCALA_HOME/bin/scalac" Inliners.scala
printf ' patch'
jar uf "$JAR" scala
cd "$BASE"
rm -r "$BASE/tmp"
echo ' done.'
