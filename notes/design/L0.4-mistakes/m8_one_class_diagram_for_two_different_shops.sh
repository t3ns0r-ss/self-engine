# A class diagram cannot tell these two shops apart: the relationships read from both headers are the same lines.
UML="node $ROOT/code/shared/uml/uml_check.mjs"
U="$ROOT/code/L0.4/same-classes-different-order"
echo "checked_first:"; $UML extract "$U/checked_first.hpp"
echo "mailed_first:";  $UML extract "$U/mailed_first.hpp"
if diff <($UML extract "$U/checked_first.hpp") <($UML extract "$U/mailed_first.hpp") > /dev/null; then echo "=> identical class diagrams"; fi
