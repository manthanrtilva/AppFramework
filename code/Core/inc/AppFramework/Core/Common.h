/// File: Common.h
/// Author : Manthan R. Tilva
/// Date : 13/09/2018
/// Brief : Contian common macros

#ifdef MSVC
#ifdef EXPORT_API
#define CLASS_API __declspec(dllexport)
#else
#define CLASS_API __declspec(dllimport)
#endif // EXPORT_API
#else
#define CLASS_API
#endif // MSVC
