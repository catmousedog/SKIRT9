/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "NestedDensityTreePolicy.hpp"
#include "FatalError.hpp"
#include "MediumSystem.hpp"
#include "TreeNode.hpp"
#include "TreeSpatialGrid.hpp"

void NestedDensityTreePolicy::setupSelfBefore()
{
    DensityTreePolicy::setupSelfBefore();

    _inner = Box(_minXInner, _minYInner, _minZInner, _maxXInner, _maxYInner, _maxZInner);

    auto ms = find<MediumSystem>(false);
    auto grid = ms->find<TreeSpatialGrid>(false);
    Box _outer = grid->boundingBox();

    if (_inner.xmin() <= _outer.xmin()) throw FATALERROR("The inner min x is outside the outer region");
    if (_inner.ymin() <= _outer.ymin()) throw FATALERROR("The inner min y is outside the outer region");
    if (_inner.zmin() <= _outer.zmin()) throw FATALERROR("The inner min z is outside the outer region");
    if (_inner.xmax() >= _outer.xmax()) throw FATALERROR("The inner max x is outside the outer region");
    if (_inner.ymax() >= _outer.ymax()) throw FATALERROR("The inner max y is outside the outer region");
    if (_inner.zmax() >= _outer.zmax()) throw FATALERROR("The inner max z is outside the outer region");

    _baseMinLevel = _minLevel;
    _baseMaxLevel = _maxLevel;
}

void NestedDensityTreePolicy::setupSelfAfter()
{
    DensityTreePolicy::setupSelfAfter();

    _minLevel = min(_minLevel, _nestedTree->_minLevel);
    _maxLevel = max(_maxLevel, _nestedTree->_maxLevel);
}

bool NestedDensityTreePolicy::needsSubdivide(TreeNode* node, int level)
{
    if (_inner.contains(node->center()))
    {
        if (level < _nestedTree->_minLevel) return true;
        if (level >= _nestedTree->_maxLevel) return false;

        return _nestedTree->needsSubdivide(node, level);
    }
    else
    {
        if (level < _baseMinLevel) return true;
        if (level >= _baseMaxLevel) return false;

        return DensityTreePolicy::needsSubdivide(node, level);
    }
}