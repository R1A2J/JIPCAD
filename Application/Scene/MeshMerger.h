#pragma once
#include "Mesh.h"
#include <LangUtils.h>
namespace Nome::Scene
{

class CMeshMerger : public CMesh
{
    //DEFINE_INPUT(float, Level) { MarkDirty(); }

    //DEFINE_OUTPUT_WITH_UPDATE(CVertexInfo*, Point) { UpdateEntity(); }
    void MarkDirty() override;
    void UpdateEntity() override;


public:
    // DECLARE_META_CLASS(CMeshMerger, CEntity);
    using Super = CMesh;
    CMeshMerger() = default;
    CMeshMerger(const std::string& name)
        : CMesh(std::move(name))
    {
    }

    // No update yet, please just use one time
    void MergeIn(const CMeshInstance& meshInstance);

    // Buggy, preset to 3 subdivision steps
    void Catmull(const CMeshInstance& meshInstance, int i);

    bool subdivide(CMeshImpl& _m, int n, const bool _update_points); 

    void split_face(CMeshImpl& _m, const CMeshImpl::FaceHandle& _fh);

    void split_edge(CMeshImpl& _m, const CMeshImpl::EdgeHandle& _eh);

    void compute_midpoint(CMeshImpl& _m, const CMeshImpl::EdgeHandle& _eh, const bool _update_points);

    void update_vertex( CMeshImpl& _m, const CMeshImpl::VertexHandle& _vh);

    bool prepare(CMeshImpl& _m);

    bool cleanup(CMeshImpl& _m);


private:
    std::pair<CMeshImpl::VertexHandle, float> FindClosestVertex(const tc::Vector3& pos);

    unsigned int VertCount = 0;
    unsigned int FaceCount = 0;

    unsigned int SubLevel = 3;

    OpenMesh::VPropHandleT< CMeshImpl::Point > vp_pos_; // next vertex pos
    OpenMesh::EPropHandleT< CMeshImpl::Point > ep_pos_; // new edge pts
    OpenMesh::FPropHandleT< CMeshImpl::Point > fp_pos_; // new face pts
    OpenMesh::EPropHandleT<double> creaseWeights_; // crease weights
};

}
