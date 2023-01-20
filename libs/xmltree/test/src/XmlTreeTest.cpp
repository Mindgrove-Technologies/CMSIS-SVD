/*
 * Copyright (c) 2020-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "gtest/gtest.h"

#include "XMLTree.h"

TEST(XmlTreeTest, Trim) {
  EXPECT_EQ(XmlItem::Trim("").empty(), true);
  EXPECT_EQ(XmlItem::Trim(" \t\n\r").empty(), true);
  EXPECT_EQ(XmlItem::Trim(" \t\n\rEnd"), "End");
  EXPECT_EQ(XmlItem::Trim("\t Middle\r\n"), "Middle");
  EXPECT_EQ(XmlItem::Trim("\t Mid with\t space \r\n"), "Mid with\t space");
  EXPECT_EQ(XmlItem::Trim("Start \r\n"), "Start");
  EXPECT_EQ(XmlItem::Trim("Full"), "Full");
}

TEST(XmlTreeTest, GetAttribute) {

  XMLTreeElement e;
  e.AddAttribute("string", "strVal");
  e.AddAttribute("yes", "true");
  e.AddAttribute("no", "false");
  e.AddAttribute("one", "1");
  EXPECT_EQ(e.GetAttributesString(), "no=false one=1 string=strVal yes=true");
  EXPECT_EQ(e.GetAttributesAsXmlString(), "no=\"false\" one=\"1\" string=\"strVal\" yes=\"true\"");

  e.AddAttribute("zero", "0");
  e.AddAttribute("empty", "");
  e.AddAttribute("zero", "0");
  e.AddAttribute("hex", "0xFFFF0000");
  e.AddAttribute("ten", "10");
  e.AddAttribute("zeroTen", "010");
  e.AddAttribute("minusOne", "-1");

  EXPECT_EQ(e.GetAttribute("unknown").empty(), true);
  EXPECT_EQ(e.GetAttribute("string"), "strVal");
  EXPECT_EQ(e.GetAttribute("empty").empty(), true);

  EXPECT_EQ(e.GetAttributeAsBool("unknown"), false);
  EXPECT_EQ(e.GetAttributeAsBool("unknown", true), true);
  EXPECT_EQ(e.GetAttributeAsBool("yes"), true);
  EXPECT_EQ(e.GetAttributeAsBool("no"), false);
  EXPECT_EQ(e.GetAttributeAsBool("one"), true);
  EXPECT_EQ(e.GetAttributeAsBool("zero"), false);

  EXPECT_EQ(e.GetAttributeAsInt("unknown"), -1);
  EXPECT_EQ(e.GetAttributeAsInt("unknown", 42), 42);
  EXPECT_EQ(e.GetAttributeAsInt("string"), -1);
  EXPECT_EQ(e.GetAttributeAsInt("one"), 1);
  EXPECT_EQ(e.GetAttributeAsInt("zero"), 0);
  EXPECT_EQ(e.GetAttributeAsInt("ten"), 10);
  EXPECT_EQ(e.GetAttributeAsInt("zeroTen"), 8);
  EXPECT_EQ(e.GetAttributeAsInt("minusOne"), -1);
  EXPECT_EQ(e.GetAttributeAsULL("hex"), 0xFFFF0000);
  EXPECT_EQ(e.GetAttributeAsULL("ten"), 10);
  EXPECT_EQ(e.GetAttributeAsULL("zeroTen"), 10);
  EXPECT_EQ(e.GetAttributeAsUnsigned("hex"), 0xFFFF0000);
  EXPECT_EQ(e.GetAttributeAsUnsigned("ten"), 10U);
  EXPECT_EQ(e.GetAttributeAsUnsigned("zeroTen"), 8); // treated as octal
  EXPECT_EQ(e.GetAttributeAsUnsigned("minusOne"), 0xFFFFFFFF);
}
