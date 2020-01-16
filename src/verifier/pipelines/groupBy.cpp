#include "verifier/verifier.hpp"

MARKUS_PIPELINE(groupBy, 1) {
  EXPECT_TYPE_SHAPE(resultType, 1);
  EXPECT_ARG_FIELD(0);
  EXPECT_ARG_FIELD_EXISTS(0);

  Type::Container labelType =
      arguments[0].asVariable()->getType().asArray()->getContainedType();
  Type::Container dataType = resultType;

  EXPECT_TYPE_SHAPE(labelType, 0);

  std::string labelName = labelType.toString();
  std::string dataName = dataType.toString();
  std::string name = "Group<" + labelName + ", " + dataName + ">";

  Type::Object* object = new Type::Object(name);
  object->set("label", labelType, false);
  object->set("data", dataType, false);

  Type::Array* array = new Type::Array(Type::Container(object));
  resultType = Type::Container(array);

  return true;
}

MARKUS_PIPELINE(groupBy, 2) {
  EXPECT_TYPE_SHAPE(resultType, 1);
  EXPECT_ARG_FIELD(0);
  EXPECT_ARG_FIELD_EXISTS(0);
  EXPECT_ARG_KIND(1, Value::VALUE_KIND_QUERY);

  Type::Container labelType =
      arguments[0].asVariable()->getType().asArray()->getContainedType();
  Type::Container dataType = arguments[1].asQuery()->getResultType();

  EXPECT_TYPE_SHAPE(labelType, 0);

  std::string labelName = labelType.toString();
  std::string dataName = dataType.toString();
  std::string name = "Group<" + labelName + ", " + dataName + ">";

  Type::Object* object = new Type::Object(name);
  object->set("label", labelType, false);
  object->set("data", dataType, false);

  Type::Array* array = new Type::Array(Type::Container(object));
  resultType = Type::Container(array);

  return true;
}