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
  if (specification.ExpectedFields_.erase(op.Key) == 0) {
    throw std::logic_error("RemoveField failed: field does not exist: " + op.Key);
  }
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const ModifyField& op) const {
  auto it = specification.ExpectedFields_.find(op.Key);
  if (it == specification.ExpectedFields_.end()) {
    throw std::logic_error("ModifyField failed: field does not exist: " + op.Key);
  }

  op.Mutator(it->second);
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const AddField& op) const {
  auto [it, inserted] = specification.ExpectedFields_.emplace(op.Key, op.Field);
  if (!inserted) {
    throw std::logic_error("AddField failed: field already exists: " + op.Key);
  }
}

void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const AddFieldOrdering& op) const {
  // if there already exists a constraint with the same before and after, we throw a logic error
  for (const auto& constraint : specification.OrderingConstraints_) {
    if (constraint.Before == op.BeforeKey && constraint.After == op.AfterKey) {
      throw std::logic_error("AddFieldOrdering failed: constraint already exists: " + op.BeforeKey +
                             " -> " + op.AfterKey);
    }
  }
  specification.OrderingConstraints_.push_back(FieldOrderingConstraint{op.BeforeKey, op.AfterKey});
}

/// @brief Helper function to apply a RemoveFieldOrdering operation to the orderings vector
/// @param constraints the ordering constraints vector to modify
/// @param op the remove field ordering operation to apply
void LayoutSpecificationBuilder::ApplyOperation(LayoutSpecification& specification,
                                                const RemoveFieldOrdering& op) const {
  auto& constraints = specification.OrderingConstraints_;

  auto it =
      std::find_if(constraints.begin(), constraints.end(), [&](const FieldOrderingConstraint& c) {
        return c.Before == op.BeforeKey && c.After == op.AfterKey;
      });

  if (it == constraints.end()) {
    throw std::logic_error("RemoveFieldOrdering failed: constraint does not exist: " +
                           op.BeforeKey + " -> " + op.AfterKey);
  }

  constraints.erase(it);
}
}  // namespace datalint::layout
