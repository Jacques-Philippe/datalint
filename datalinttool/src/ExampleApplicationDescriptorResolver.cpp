#include <ExampleApplicationDescriptorResolver.h>
#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>

#include <sstream>

namespace {
const std::string kApplicationNameKey = "ApplicationName";
const std::string kApplicationVersionKey = "ApplicationVersion";
}  // namespace

datalint::ResolveResult ExampleApplicationDescriptorResolver::Resolve(
    const datalint::RawData& rawData) {
  datalint::ResolveResult result;
  if (!rawData.HasKey(kApplicationNameKey)) {
    result.Errors.push_back("Missing required field: " + kApplicationNameKey);
    result.Success = false;
    return result;
  }
  if (!rawData.HasKey(kApplicationVersionKey)) {
    result.Errors.push_back("Missing required field: " + kApplicationVersionKey);
    result.Success = false;
    return result;
  }
  const auto nameFields = rawData.GetFieldsByKey(kApplicationNameKey);
  const auto versionFields = rawData.GetFieldsByKey(kApplicationVersionKey);
  if (nameFields.size() > 1) {
    result.Errors.push_back("Found more than one match for: " + kApplicationNameKey +
                            "\nThis should be unique");
    result.Success = false;
    return result;
  }
  if (versionFields.size() > 1) {
    result.Errors.push_back("Found more than one match for: " + kApplicationVersionKey +
                            "\nThis should be unique");
    result.Success = false;
    return result;
  }
  // in our example application, we know what our input file looks like
  // we just take the first occurrence of each field
  auto getFirstCsvField = [](const std::string& s) -> std::string {
    auto pos = s.find(',');
    if (pos == std::string::npos) return s;  // no comma found
    return s.substr(0, pos);
  };

  result.Descriptor.Name = getFirstCsvField(nameFields.front()->Value);
  result.Descriptor.Version = getFirstCsvField(versionFields.front()->Value);
  result.Success = true;
  return result;
}
