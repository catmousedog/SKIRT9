/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef NESTEDDENSITYTREEPOLICY_HPP
#define NESTEDDENSITYTREEPOLICY_HPP

#include "Box.hpp"
#include "DensityTreePolicy.hpp"

/** NestedDensityTreePolicy is a tree policy that allows for nesting DensityTreePolicies, enabling
    users to define a region containing another density tree. The inner and outer regions can have
    different properties, utilizing all properties from DensityTreePolicy.

    This class inherits from DensityTreePolicy and uses all the inherited properties to classify the
    outer region. Additionally, it introduces an additional property called nestedTree, which is
    also a DensityTreePolicy. The nestedTree property decides the properties of the inner region.

    The nestedTree property can also be another NestedDensityTreePolicy, allowing for recursive
    nesting. 

    When determining whether a TreeNode intersects with the inner 'nested' region, if it does, the
    node will be subdivided. This can result in a smooth transition, as larger TreeNodes may only
    need to subdivide once or a few times, making them no longer intersect with the inner region.
    Boxes that just intersect the inner region, especially at the edge, will only subdivide a few
    times before they no longer intersect, providing a relatively smooth transition from the outer
    to inner region. */
class NestedDensityTreePolicy : public DensityTreePolicy
{
    ITEM_CONCRETE(NestedDensityTreePolicy, DensityTreePolicy,
                  "a tree grid construction policy using a nested density tree policy")
        ATTRIBUTE_TYPE_DISPLAYED_IF(NestedDensityTreePolicy, "Level2")

        PROPERTY_DOUBLE(minXInner, "the start point of the inner box in the X direction")
        ATTRIBUTE_QUANTITY(minXInner, "length")

        PROPERTY_DOUBLE(maxXInner, "the end point of the inner box in the X direction")
        ATTRIBUTE_QUANTITY(maxXInner, "length")

        PROPERTY_DOUBLE(minYInner, "the start point of the inner box in the Y direction")
        ATTRIBUTE_QUANTITY(minYInner, "length")

        PROPERTY_DOUBLE(maxYInner, "the end point of the inner box in the Y direction")
        ATTRIBUTE_QUANTITY(maxYInner, "length")

        PROPERTY_DOUBLE(minZInner, "the start point of the inner box in the Z direction")
        ATTRIBUTE_QUANTITY(minZInner, "length")

        PROPERTY_DOUBLE(maxZInner, "the end point of the inner box in the Z direction")
        ATTRIBUTE_QUANTITY(maxZInner, "length")

        PROPERTY_ITEM(nestedTree, DensityTreePolicy, "the nested density tree inside the inner region")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function checks whether the inner region is inside the outer region. It also copies the
     * minLevel and maxLevel as these determine the refinement of the outer region. */
    void setupSelfBefore() override;

    /** This function calculates the minLevel and maxLevel values used in the inherited function
        constructTree. The minLevel is the minimum value among all the minLevel of all the child
        nestedTrees. The maxLevel is the maximum value among all the maxLevel of all the child
        nestedTrees. */
    void setupSelfAfter() override;

    //======================== Other Functions =======================

public:
    /** This function determines whether a given node needs to be subdivided for a given level. If
        the node intersects with the inner region, the level must lie between the minLevel and
        maxLevel of the inner region. If the node is not within the inner region, it will use the
        baseMinLevel and baseMaxLevel as bounds. If the node is within all the refinement bounds
        then it will use the needsSubdidive function of the corresponding DensityTreePolicy. */
    bool needsSubdivide(TreeNode* node, int level) override;

    //======================== Data Members ========================

private:
    // the inner region bounds
    Box _inner;

    // the refinement bounds for the outer region
    int _baseMinLevel;
    int _baseMaxLevel;
};

#endif