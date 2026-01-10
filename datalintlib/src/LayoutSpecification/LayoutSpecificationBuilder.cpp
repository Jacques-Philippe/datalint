#include <datalint/LayoutSpecification/LayoutSpecificationBuilder.h>

namespace datalint::layout {

LayoutSpecification LayoutSpecificationBuilder::Build(Version version,
                                                      std::span<const LayoutPatch> patches) const {
  std::map<std::string, ExpectedField> fields;

  for (const auto& patch : patches) {
    if (!patch.AppliesTo.Contains(version)) {
      continue;
    }

    ApplyPatch(fields, patch);
  }

  return LayoutSpecification{std::move(fields)};
}

void LayoutSpecificationBuilder::ApplyPatch(std::map<std::string, ExpectedField>& fields,
                                            const LayoutPatch& patch) const {
  for (const auto& op : patch.Operations) {
    std::visit([&](const auto& operation) { ApplyOperation(fields, operation); }, op);
  }
}

void LayoutSpecificationBuilder::ApplyOperation(std::map<std::string, ExpectedField>& fields,
                                                const RemoveField& op) const {
  if (fields.erase(op.Key) == 0) {
    throw std::logic_error("RemoveField failed: field does not exist: " + op.Key);
  }
}

void LayoutSpecificationBuilder::ApplyOperation(std::map<std::string, ExpectedField>& fields,
                                                const ModifyField& op) const {
  auto it = fields.find(op.Key);
  if (it == fields.end()) {
    throw std::logic_error("ModifyField failed: field does not exist: " + op.Key);
  }

  op.Mutator(it->second);
}

void LayoutSpecificationBuilder::ApplyOperation(std::map<std::string, ExpectedField>& fields,
                                                const AddField& op) const {
  auto [it, inserted] = fields.emplace(op.Key, op.Field);
  if (!inserted) {
    throw std::logic_error("AddField failed: field already exists: " + op.Key);
  }
}

}  // namespace datalint::layout
