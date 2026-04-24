/**
 * @file Translation.hpp
 * @author Hyuncheol
 * @date 2026-04-23
 * @brief main file to test
 */

#include <iostream>
#include "TransformationPipeline.hpp"
#include "Translation.hpp"
#include "Scale.hpp"

int main() {
    TransformationPipeline pipeline;

    // test enqueueTransform
    pipeline.enqueueTransform(new Translation(1, 2, 3));
    pipeline.enqueueTransform(new Scale(2));
    pipeline.enqueueTransform(new Translation(0, -1, 0));
    std::cout << "Length after 3 enqueues: " << pipeline.getLength() << std::endl; // 3

    // test runFullPipeline
    Vector3D point(1, 1, 1);
    pipeline.runFullPipeline(point);
    std::cout << "After runFullPipeline: ("
              << point.getX() << ", " << point.getY() << ", " << point.getZ()
              << ")" << std::endl; // (1+1,1+2,1+3)=>(2,3,4)*2=>(4,6,8)+(0,-1,0)=>(4,5,8)
    std::cout << "Pipeline length unchanged: " << pipeline.getLength() << std::endl; // 3

    // test processNextTransform
    Vector3D point2(0, 0, 0);
    pipeline.processNextTransform(point2); // applies Translation(1,2,3)
    std::cout << "After processNext: ("
              << point2.getX() << ", " << point2.getY() << ", " << point2.getZ()
              << ")" << std::endl; // (1,2,3)
    std::cout << "Pipeline length after processNext: " << pipeline.getLength() << std::endl; // 2

    // test reversePipeline
    TransformationPipeline pipeline2;
    pipeline2.enqueueTransform(new Translation(1, 0, 0));
    pipeline2.enqueueTransform(new Scale(3));
    pipeline2.enqueueTransform(new Translation(0, 0, 5));
    pipeline2.reversePipeline();
    // Should now be: Translation(0,0,5) -> Scale(3) -> Translation(1,0,0)
    std::cout << "After reverse, types: "
              << pipeline2.getEntry(1)->getType() << ", "
              << pipeline2.getEntry(2)->getType() << ", "
              << pipeline2.getEntry(3)->getType() << std::endl;

    // test removeTransformationsOfType
    TransformationPipeline pipeline3;
    pipeline3.enqueueTransform(new Translation(1, 0, 0));
    pipeline3.enqueueTransform(new Scale(2));
    pipeline3.enqueueTransform(new Translation(0, 1, 0));
    pipeline3.enqueueTransform(new Scale(3));
    int removed = pipeline3.removeTransformationsOfType("SCALE");
    std::cout << "Removed: " << removed << std::endl;           // 2
    std::cout << "Remaining: " << pipeline3.getLength() << std::endl; // 2

    // test empty pipeline edge case
    TransformationPipeline empty;
    Vector3D p(5, 5, 5);
    empty.processNextTransform(p); // should do nothing
    std::cout << "Empty processNext unchanged: ("
              << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")" << std::endl;

    return 0;
}
