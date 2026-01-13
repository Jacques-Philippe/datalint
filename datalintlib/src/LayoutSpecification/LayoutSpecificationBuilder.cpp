#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>
#include <datalint/LayoutSpecification/LayoutSpecificationBuilder.h>

namespace datalint::layout {

LayoutSpecification LayoutSpecificationBuilder::Build(Version version,
                                                      std::span<const LayoutPatch> patches) const {
  LayoutSpecification spec;

  for (const auto& patch : patches) {
    if (!patch.AppliesTo().Contains(version)) {
      continue;
    }

    ApplyPatch(spec, patch);
  }

  return spec;
}

void LayoutSpecificationBuilder::ApplyPatch(LayoutSpecification& specification,
                                            const LayoutPatch& patch) const {
  for (const auto& op : patch.Operations()) {
    std::visit([&](const auto& operation) { ApplyOperation(specification, operation); }, op);
  }
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const RemoveField& op) const {
  specification.RemoveExpectedField(op.Key);
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const ModifyField& op) const {
  specification.ModifyExpectedField(op.Key, op.Mutator);
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const AddField& op) const {
  specification.AddExpectedField(op.Key, op.Field);
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const AddFieldOrdering& op) const {
  specification.AddOrderingConstraint(FieldOrderingConstraint{op.BeforeKey, op.AfterKey});
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const RemoveFieldOrdering& op) const {
  specification.RemoveOrderingConstraint(op.BeforeKey, op.AfterKey);
}
}  // namespace datalint::layout
