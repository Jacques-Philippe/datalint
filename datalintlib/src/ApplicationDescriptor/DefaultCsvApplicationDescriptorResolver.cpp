#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>
#include <datalint/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.h>
#include <datalint/ApplicationDescriptor/ResolveError.h>
#include <datalint/ApplicationDescriptor/ResolveResult.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>

namespace {
const std::string kApplicationNameKey = "ApplicationName";
const std::string kApplicationVersionKey = "ApplicationVersion";
}  // namespace

namespace datalint {
ResolveResult DefaultCsvApplicationDescriptorResolver::Resolve(const datalint::RawData& rawData) {
  datalint::ResolveResult result;
  if (!rawData.HasKey(kApplicationNameKey)) {
    result.Errors.push_back(
        ResolveError{ResolveErrorCode::MissingRequiredField, kApplicationNameKey});
    return result;
  }
  if (!rawData.HasKey(kApplicationVersionKey)) {
    result.Errors.push_back(
        ResolveError{ResolveErrorCode::MissingRequiredField, kApplicationVersionKey});
    return result;
  }
  const auto nameFields = rawData.GetFieldsByKey(kApplicationNameKey);
  const auto versionFields = rawData.GetFieldsByKey(kApplicationVersionKey);
  if (nameFields.size() > 1) {
    result.Errors.push_back(ResolveError{ResolveErrorCode::DuplicateField, kApplicationNameKey});
    return result;
  }
  if (versionFields.size() > 1) {
    result.Errors.push_back(ResolveError{ResolveErrorCode::DuplicateField, kApplicationVersionKey});
    return result;
  }
  // in our example application, we know what our input file looks like
  // we just take the first occurrence of each field
  auto getFirstCommaSeparatedValue = [](const std::string& s) -> std::string {
    auto pos = s.find(',');
    if (pos == std::string::npos) return s;  // no comma found
    return s.substr(0, pos);
  };
  result.Descriptor.emplace();
  result.Descriptor->Name = getFirstCommaSeparatedValue(nameFields.front()->Value);
  result.Descriptor->Version = getFirstCommaSeparatedValue(versionFields.front()->Value);
  return result;
}
}  // namespace datalint
