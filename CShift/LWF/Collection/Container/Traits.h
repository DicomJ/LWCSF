#ifndef CSHIFT_LWF_COLLECTION_CONTAINER_TRAITS_H
#define CSHIFT_LWF_COLLECTION_CONTAINER_TRAITS_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Traits/Prediction.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Container {

template <typename Container>
struct Traits {
  template <typename T> struct Is;
};

template <typename Container>
template <typename T>
struct Traits<Container>::Is {

  static const Bool count =
      LWF::Type<typename LWF::Type<T>::Kind>::Is::
          Equal::template To<typename LWF::Type<UInt>::Kind>::type;
  static const Bool Type =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Type>::type;
  static const Bool Iterator =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Iterator>::type;
  static const Bool Nonconst =
          LWF::Type<T>::Is::nonconst;
};

}}}} // namespace CShift::LWF::Collection::Container

#endif // CSHIFT_LWF_COLLECTION_CONTAINER_TRAITS_H
