# A member is added to Shop in the header; the diagram that was drawn before is not touched.
UML="node $ROOT/code/shared/uml/uml_check.mjs"
sed 's|^class Shop {|class Audit { public: void note() {} };\nclass Shop {|; s|^    Catalog catalog_;|    Catalog catalog_;\n    Audit audit_;|' "$ROOT/code/L0.4/shop-model/shop.hpp" > "$B/shop.hpp"
$UML classes "$ROOT/code/L0.4/shop-model/diagram.mmd" "$B/shop.hpp"
