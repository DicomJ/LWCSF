#ifndef CSHIFT_TEXT_COLLECTION_STRING_H
#define CSHIFT_TEXT_COLLECTION_STRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/CString.h"
#include "Text/Character/Code/Case/Transcoding.h"
#include "LWF/Initializer/List.h"
#include "LWF/Algorithm/Find/Exactly.h"
#include "LWF/Algorithm/Find/One/Of.h"
#include "LWF/Algorithm/Find/One/Not/Of.h"
#include "LWF/Algorithm/Equal/Exactly.h"
#include "LWF/Algorithm/Different/Exactly.h"
#include "LWF/Value/Range.h"


namespace CShift {
namespace Text {
namespace Collection {

template <typename Encoding_, typename Base>
struct String : Base, Encoding_ {

  private: template <typename T> struct Is;
  public: typedef Encoding_ Encoding;
  public: typedef typename Encoding::Char Char;
  public: typedef Text::CString<const Char> CString;
  public: typedef typename Base::Allocator Allocator;
  public: typedef typename Base::Iterator Iterator;
  public: static const UInt toEnd = Int(-1);
  public: static const UInt notFound = Int(-1);

  String(const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator())
    : Base(allocator), Encoding(encoding) {}

  String(const Allocator &allocator,
         const Encoding &encoding = Encoding())
    : Base(allocator), Encoding(encoding) {}

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  String(String &&string)
    : Base(LWF::Forward::reference<Base>(string)),
           Encoding(LWF::Forward::reference<Encoding>(string)) {}
  String &operator = (String &&string) {
    Base::operator = (LWF::Forward::reference<Base>(string));
    Encoding::operator = (LWF::Forward::reference<Encoding>(string));
    return *this;
  }
  #endif // C++11

  String(const Char &ch,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator())
    : Base(operand(ch), allocator), Encoding(encoding) {}
  String(UInt count, const Char &ch,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator())
    : Base(operand(count, ch), allocator), Encoding(encoding) { }
  String(const CString &cstring,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator())
    : Base(operand(cstring), allocator), Encoding(encoding) { }
  String(const CString &cstring, UInt size,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator())
    : Base(operand(cstring, size), allocator), Encoding(encoding) { }
  template <typename Range>
  String(const Range &range,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator(),
         typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0)
    : Base(operand(range), allocator), Encoding(encoding) { }
  template <typename Iterator>
  String(const Iterator &first, const Iterator &last,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator(),
         typename LWF::Traits::Prediction<!Is<Iterator>::integralRange>::Type * = 0)
    : Base(allocator), Encoding(encoding) { assign(first, last); }
  template <typename E, typename B>
  /*explicit */String(const String<E, B> &string,
                  const Encoding &encoding = Encoding(),
                  const Allocator &allocator = Allocator())
    : Base(operand(string), allocator), Encoding(encoding) {
  }

  CString cstring() const {
    { String &This = const_cast<String &>(*this);
      This.pushBack(Char(0)); This.popBack(); }
    return &*Base::begin();
  }

  template <typename U>
  Void pushBack(const U &u) {
    Base::pushBack(operand(u));
  }
  template <typename U, typename UU>
  Void pushBack(const U &u, const UU &uu) {
    Base::pushBack(operand(u, uu));
  }
  template <typename U>
  Void pushFront(const U &u) {
    Base::pushFront(operand(u));
  }
  template <typename U, typename UU>
  Void pushFront(const U &u, const UU &uu) {
    Base::pushFront(operand(u, uu));
  }
  template <typename Where, typename U>
  Iterator insert(const Where &where, const U &u) {
    return insert_(where, operand(u));
  }
  template <typename Where, typename U, typename UU>
  Iterator insert(const Where &where, const U &u, const UU &uu) {
    return insert_(where, operand(u, uu));
  }
  Iterator erase(UInt position = 0, UInt count = toEnd) {
    return erase_(this->range(position, count));
  }
  template <typename Iterator>
  Iterator erase(const Iterator &iterator,
                 typename LWF::Traits::Prediction<!Is<Iterator>::position>::Type * = 0) {
    return Base::erase(iterator);
  }
  template <typename Iterator>
  Iterator erase(const Iterator &first, const Iterator &last,
                 typename LWF::Traits::Prediction<!Is<Iterator>::integralRange>::Type * = 0) {
    return Base::erase(first, last);
  }
  template <typename U>
  String &assign(const U &u) {
    return Base::assign(operand(u)), *this;
  }
  template <typename U, typename UU>
  String &assign(const U &u, const UU &uu) {
    return Base::assign(operand(u, uu)), *this;
  }
  template <typename U>
  String &append(const U &u) {
    return Base::pushBack(operand(u)), *this;
  }
  template <typename U, typename UU>
  String &append(const U &u, const UU &uu) {
    return Base::pushBack(operand(u, uu)), *this;
  }
  template <typename U>
  String addFront(const U &u) const {
    return addFront_(operand(u));
  }
  template <typename U, typename UU>
  String addFront(const U &u, const UU &uu) const {
    return addFront_(operand(u, uu));
  }
  template <typename U>
  String addBack(const U &u) const {
    return addBack_(operand(u)); return *this;
  }
  template <typename U, typename UU>
  String addBack(const U &u, const UU &uu) const {
    return addBack_(operand(u, uu));
  }
  template <typename U>
  Bool equal(const U &u) const {
    return Base::operator == (operand(u));
  }
  template <typename U, typename UU>
  Bool equal(const U &u, const UU &uu) const {
    return Base::operator == (operand(u, uu));
  }  template <typename U>
  Int different(const U &u) const {
    return Base::operator - (operand(u));
  }
  template <typename U, typename UU>
  Int different(const U &u, const UU &uu) const {
    return Base::operator - (operand(u, uu));
  }
  template <typename U>
  UInt find(const U &u, UInt position = 0, UInt count = toEnd) const {
    return search<LWF::Algorithm::Find::Exactly>(u, position, count);
  }
  template <typename U, typename UU>
  UInt find(const U &u, const UU &uu, UInt position, UInt count) const {
    return search<LWF::Algorithm::Find::Exactly>(u, uu, position, count);
  }
  template <typename U>
  UInt rfind(const U &u, UInt position = 0, UInt count = toEnd) const {
    return rsearch<LWF::Algorithm::Find::Exactly>(u, position, count);
  }
  template <typename U, typename UU>
  UInt rfind(const U &u, const UU &uu, UInt position, UInt count) const {
    return rsearch<LWF::Algorithm::Find::Exactly>(u, uu, position, count);
  }
  template <typename U>
  UInt findFirstOf(const U &u, UInt position = 0, UInt count = toEnd) const {
    return search<LWF::Algorithm::Find::One::Of>(u, position, count);
  }
  template <typename U, typename UU>
  UInt findFirstOf(const U &u, const UU &uu, UInt position, UInt count) const {
    return search<LWF::Algorithm::Find::One::Of>(u, uu, position, count);
  }
  template <typename U>
  UInt findLastOf(const U &u, UInt position = 0, UInt count = toEnd) const {
    return rsearch<LWF::Algorithm::Find::One::Of>(u, position, count);
  }
  template <typename U, typename UU>
  UInt findLastOf(const U &u, const UU &uu, UInt position, UInt count) const {
    return rsearch<LWF::Algorithm::Find::One::Of>(u, uu, position, count);
  }
  template <typename U>
  UInt findFirstNotOf(const U &u, UInt position = 0, UInt count = toEnd) const {
    return search<LWF::Algorithm::Find::One::Not::Of>(u, position, count);
  }
  template <typename U, typename UU>
  UInt findFirstNotOf(const U &u, const UU &uu, UInt position, UInt count) const {
    return search<LWF::Algorithm::Find::One::Not::Of>(u, uu, position, count);
  }
  template <typename U>
  UInt findLastNotOf(const U &u, UInt position = 0, UInt count = toEnd) const {
    return rsearch<LWF::Algorithm::Find::One::Not::Of>(u, position, count);
  }
  template <typename U, typename UU>
  UInt findLastNotOf(const U &u, const UU &uu, UInt position, UInt count) const {
    return rsearch<LWF::Algorithm::Find::One::Not::Of>(u, uu, position, count);
  }
  template <typename How, typename U>
  UInt search(const U &u, UInt position = 0, UInt count = toEnd,
              const How &how = How()) const {
    return search_(how, Base::begin(), range(position, count), operand(u));
  }
  template <typename How, typename U, typename UU>
  UInt search(const U &u, const UU &uu, UInt position, UInt count, const How &how = How()) const {
    return search_(how, Base::begin(), range(position, count), operand(u, uu));
  }
  template <typename How, typename U>
  UInt rsearch(const U &u, UInt position = 0, UInt count = toEnd,
               const How &how = How()) const {
    return rsearch_(how, Base::rbegin(), rrange(position, count),
                    LWF::Reverse::range(operand(u)));
  }
  template <typename How, typename U, typename UU>
  UInt rsearch(const U &u, const UU &uu, UInt position, UInt count, const How &how = How()) const {
    return rsearch_(how, Base::rbegin(), rrange(position, count),
                    LWF::Reverse::range(operand(u, uu)));
  }
  template <typename U>
  typename Base::Const::Iterator replace(UInt position, UInt count, const U &u) {
    return replace_(this->range(position, count), operand(u));
  }
  template <typename U, typename UU>
  typename Base::Const::Iterator replace(UInt position, UInt count, const U &u, const UU &uu) {
    return replace_(this->range(position, count), operand(u, uu));
  }
  template <typename Iterator, typename U>
  Iterator replace(const Iterator &first, const Iterator &last, const U &u,
                  typename LWF::Traits::Prediction<!Is<Iterator>::integralRange>::Type * = 0) {
    return replace_(LWF::range(first, last), operand(u));
  }
  template <typename Iterator, typename U, typename UU>
  Iterator replace(const Iterator &first, const Iterator &last, const U &u, const UU &uu,
                  typename LWF::Traits::Prediction<!Is<Iterator>::integralRange>::Type * = 0) {
    return replace_(LWF::range(first, last), operand(u, uu));
  }

  template <typename U>
  String &operator =  (const U &u) { return assign(u);            }
  template <typename U>
  String &operator += (const U &u) { return append(u);            }
  template <typename U>
  String  operator +  (const U &u) const { return addBack(u);     }
  template <typename U>
  Bool operator == (const U &u) const { return equal(u);          }
  template <typename U>
  Bool operator != (const U &u) const { return !operator == (u);  }
  template <typename U>
  Int  operator -  (const U &u) const { return different(u);     }
  template <typename U>
  Bool operator >  (const U &u) const { return (*this - u) >  0;  }
  template <typename U>
  Bool operator >= (const U &u) const { return (*this - u) >= 0;  }
  template <typename U>
  Bool operator <  (const U &u) const { return (*this - u) < 0;   }
  template <typename U>
  Bool operator <= (const U &u) const { return (*this - u) <= 0;  }

  LWF::Range<typename Base::Const::Iterator>
  range(UInt position = 0, UInt count = toEnd) const {
    return LWF::range(*this).range(position, count);
  }
  LWF::Range<typename Base::Const::Reverse::Iterator>
  rrange(UInt position = 0, UInt count = toEnd) const {
    return LWF::range(Base::rbegin(), Base::rend()).range(position, count);
  }

  const Encoding &encoding() const { return *this; }
  String toUpper() const {
    typedef typename Encoding::Case::template Upper<Encoding, Iterator> Case;
    return transcode(*this, Case(encoding(), Base::begin(), Base::end()));
  }
  String toLower() const {
    typedef typename Encoding::Case::template Lower<Encoding, Iterator> Case;
    return transcode(*this, Case(encoding(), Base::begin(), Base::end()));
  }
  String toFolded() const {
    typedef typename Encoding::Case::template Folded<Encoding, Iterator> Case;
    return transcode(*this, Case(encoding(), Base::begin(), Base::end()));
  }
  String toTitle() const {
    typedef typename Encoding::Case::template Title<Encoding, Iterator> Case;
    return transcode(*this, Case(encoding(), Base::begin(), Base::end()));
  }

  //private: typedef Char Type;

  private: template <typename Case, typename E, typename B>
  String transcode(const String<E, B> &original, const Case &case_) const {

    String string(this->encoding(), this->allocator());
    string.ensureBackCapacity(original.size());

    typename String      ::Encoding::Encoder encoder(string);
    typename String      ::Encoding::Encoder::Output encoded;
    typename String<E, B>::Encoding::Decoder decoder(original);
    typename String<E, B>::Encoding::Decoder::Output decoded;

    for (typename String<E, B>::Const::Iterator iterator = original.begin();
         iterator != original.end(); iterator += decoded.size()) {
      decoded = decoder(iterator, original.end());
      encoded = encoder(case_(decoded.point(), iterator));
      string.pushBack(encoded.print());
    }
    return string;
  }
  private: template <typename E, typename B>
  String transcode(const String<E, B> &original) const {
    return transcode(original,
                     Text::Character::Code::Case::Transcoding<Encoding, Iterator>(
                       encoding(), original.begin(), original.end()));
  }

  private: template <typename B> Base
  operand(const String<Encoding, B> &string,
          typename LWF::Traits::Prediction<Is<String<Encoding, B> >::transcodable>::Type * = 0) const {
    if (this->encoding() != string.encoding()) {
      return transcode(string);
    } else { return string; }
  }
  private: template <typename E, typename B> Base
  operand(const String<E, B> &string,
          typename LWF::Traits::Prediction<Is<String<E, B> >::transcodable>::Type * = 0) const {
    return transcode(string);
  }
  private: template <typename E, typename B> const B &
  operand(const String<E, B> &string,
          typename LWF::Traits::Prediction<!Is<String<E, B> >::transcodable>::Type * = 0) const {
    return string;
  }
  private: static typename LWF::Value<const Char>::template Range<UInt>
  operand(const Char &ch) {
    return operand(1, ch);
  }
  private: static typename LWF::Value<const Char>::template Range<UInt>
  operand(UInt count, const Char &ch) {
    return typename LWF::Value<const Char>::template Range<UInt>(&ch, 0, count);
  }
  private: static typename CString::Range
  operand(const CString &cstring) {
    return cstring.range();
  }
  private: static typename CString::Range
  operand(const CString &cstring, UInt size) {
    return cstring.range(size);
  }
  private: template <typename Iterator> static LWF::Range<Iterator>
  operand(const Iterator &first, const Iterator &last,
          typename LWF::Traits::Prediction<!Is<Iterator>::integralRange>::Type * = 0) {
    return LWF::range(first, last);
  }
  private: template <typename Range> static const Range&
  operand(const Range &range,
          typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0) {
    return range;
  }
  private: template <typename Where, typename What>
  Iterator insert_(const Where &where, const What &what,
               typename LWF::Traits::Prediction<Is<Where>::position>::Type * = 0) {
    return Base::insert(LWF::range(*this).position(where), what);
  }
  private: template <typename Where, typename What>
  Where insert_(const Where &where, const What &what,
               typename LWF::Traits::Prediction<!Is<Where>::position>::Type * = 0) {
    return Base::insert(where, what);
  }
  private: template<typename Range>
  typename Range::Iterator erase_(const Range &range) {
    return Base::erase(range.begin(), range.end());
  }
  private: template <typename Range>
  String addFront_(const Range &range) const {
    String string; string.ensureBackCapacity(range.size() + Base::size());
    return (string += range) += *this;
  }
  private: template <typename Range>
  String addBack_(const Range &range) const {
    String string; string.ensureBackCapacity(Base::size() + range.size());
    return (string += *this) += range;
  }
  private: template <typename How, typename Iterator_, typename Iterator, typename What>
  UInt search_(const How &how,
               const Iterator_ &begin, const Iterator &first, const Iterator &last,
              const What &what) const {
    const Iterator iterator = LWF::range(first, last).search(how, what);
    return iterator != last ? iterator - begin : notFound;
  }
  private: template <typename How, typename Iterator, typename Range, typename What>
  UInt search_(const How &how,
               const Iterator &begin, const Range &range, const What &what) const {
    return search_(how, begin, range.begin(), range.end(), what);
  }
  private: template <typename How, typename Iterator, typename Range, typename What>
  UInt rsearch_(const How &how,
                const Iterator &begin, const Range &range,
                const What &what) const {
    UInt found = search_(how, begin, range, what);
    return found != notFound ? Base::size() - found : found;
  }
  private: template <typename What, typename With>
  typename What::Iterator replace_(const What &what, const With &with) {
    return replace_(what, with.begin(), with.end());
  }
  private: template <typename What, typename With>
  typename What::Iterator replace_(const What &what, const With &withFirst, const With &withLast,
                   typename LWF::Traits::Prediction<!Is<With>::Iterator>::Type * = 0) {
    return Base::insert(Base::erase(what.begin(), what.end()), withFirst, withLast);
  }
  private: template <typename What, typename With>
  typename What::Iterator replace_(const What &what, const With &withFirst, const With &withLast,
                   typename LWF::Traits::Prediction<Is<With>::Iterator>::Type * = 0) {
    return erase_(LWF::range(Base::insert(what.begin(), withFirst, withLast), what.size()));
  }

  public:
  #if PLATFORM_COMPILER_INITIALIZER_LIST
  String(const LWF::Initializer::List<Char> &list,
         const Encoding &encoding = Encoding(),
         const Allocator &allocator = Allocator())
    : Base(allocator), Encoding(encoding) { assign(list); }
  String &operator = (const LWF::Initializer::List<Char> &list) {
    return assign(list);
  }
  Void pushBack(const LWF::Initializer::List<Char> &list) {
    Base::pushBack(list);
  }
  Void pushFront(const LWF::Initializer::List<Char> &list) {
    Base::pushFront(list);
  }
  template <typename Where>
  Iterator insert(const Where &where,
                  const LWF::Initializer::List<Char> &list,
                  typename LWF::Traits::Prediction<Is<Where>::position>::Type * = 0) {
    return Base::insert(LWF::range(*this).position(where), list);
  }
  template <typename Where>
  Iterator insert(const Where &where,
                  const LWF::Initializer::List<Char> &list,
                  typename LWF::Traits::Prediction<!Is<Where>::position>::Type * = 0) {
    return Base::insert(where, list);
  }
  String &assign(const LWF::Initializer::List<Char> &list) {
    return Base::assign(list), *this;
  }
  String &operator += (const LWF::Initializer::List<Char> &list) {
    return append(list);
  }
//  String &append(const LWF::Initializer::List<Char> &list) {
//    return Base::pushBack(list), *this;
//  }
//  Bool equal(const LWF::Initializer::List<Char> &list) const {
//    return Base::operator == (list);
//  }
//  Int different(const LWF::Initializer::List<Char> &list) const {
//    return Base::operator - (list);
//  }
//  String addFront(const LWF::Initializer::List<Char> &list) const {
//    return addFront_(list);
//  }
//  String addBack(const LWF::Initializer::List<Char> &list) const {
//    return addBack_(list);
//  }
  private: const LWF::Initializer::List<Char> &
  operand(const LWF::Initializer::List<Char> &list) {
    return list;
  }
  #endif // PLATFORM_COMPILER_INITIALIZER_LIST
};

template <typename U, typename E, typename B>
String<E, B> operator +  (const U &u, const String<E, B> &string) { return string.addFront(u);      }
template <typename U, typename E, typename B>
Bool operator == (const U &u, const String<E, B> &string) { return string.operator == (u);  }
template <typename U, typename E, typename B>
Bool operator != (const U &u, const String<E, B> &string) { return string.operator != (u);  }
template <typename U, typename E, typename B>
Int  operator -  (const U &u, const String<E, B> &string) { return-string.operator -  (u);  }
template <typename U, typename E, typename B>
Bool operator >  (const U &u, const String<E, B> &string) { return string.operator <  (u);  }
template <typename U, typename E, typename B>
Bool operator >= (const U &u, const String<E, B> &string) { return string.operator <= (u);  }
template <typename U, typename E, typename B>
Bool operator <  (const U &u, const String<E, B> &string) { return string.operator >  (u);  }
template <typename U, typename E, typename B>
Bool operator <= (const U &u, const String<E, B> &string) { return string.operator >= (u);  }

template <typename Encoding, typename Base>
template <typename T>
struct String<Encoding, Base>::Is {
  static const Bool count =
      LWF::Type<typename LWF::Type<T>::Kind>::Is::
          Equal::template To<typename LWF::Type<UInt>::Kind>::type;
  static const Bool position = count;
  static const Bool integralRange = position && count;
  static const Bool range = LWF::Type<T>::Is::range/* &&
                            !LWF::Type<T>::Is::Castable::template To<String>::type*/;
  static const Bool Iterator =
      LWF::Type<T>::Is::Castable::template
            To<typename String::Iterator>::type;

  template <typename S = T> struct Same;
  template <typename E, typename B>
  struct Same <String<E, B> > {
      static const Bool encoding = False;
  };
  template <typename B>
  struct Same <String<Encoding, B> > {
      static const Bool encoding = True;
  };
  static const Bool transcodable = !Same<>::encoding || LWF::Type<T>::Is::nonconst;
};

}}} // namespace CShift::Text::Collection

#endif // CSHIFT_TEXT_COLLECTION_STRING_H
