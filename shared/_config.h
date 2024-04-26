#pragma once

#define QOSMETICS_SABERS_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
#define QOSMETICS_SABERS_EXPORT_FUNC extern "C" QOSMETICS_SABERS_EXPORT
#else
#define QOSMETICS_SABERS_EXPORT_FUNC QOSMETICS_SABERS_EXPORT
#endif
