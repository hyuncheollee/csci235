/**
 * @file Translation.hpp
 * @author Hyuncheol Lee
 * @date 2026-04-20
 * @brief Implements the TransformationPipeline class, which manages an ordered sequence of Transformation objects using a LinkedList.
 */

#include "TransformationPipeline.hpp"

/**
 * @param transform: A pointer to a Transformation object.
 * @post: The transformation is appended to the end of the pipeline.
 */
void TransformationPipeline::enqueueTransform(Transformation* transform) {
    insert(getLength() + 1, transform);
}

/**
 * @param point: A reference to a Vector3D to be transformed.
 * @post: The first transformation is applied to the point, removed from the pipeline, a * If the pipeline is empty, the point is unchanged.
 */
void TransformationPipeline::processNextTransform(Vector3D& point) {
    if (isEmpty()) return;

    Transformation* t = getEntry(1);
    point = t -> apply(point);
    remove(1);
    delete t;
}

/**
 * @param point: A reference to a Vector3D to be transformed.
 * @post: All transformations are applied to the point sequentially.
 * The pipeline remains unchanged.
 */
void TransformationPipeline::runFullPipeline(Vector3D& point) {
    int length = getLength();

    for (int i = 1; i <= length; i++) {
        point = getEntry(i) -> apply(point);
    }
}

/**
 * @post: The order of all transformations in the pipeline is reversed.
 * Example: [T1 -> T2 -> S1] becomes [S1 -> T2 -> T1]
 */
void TransformationPipeline::reversePipeline() {
    if (itemCount_ <= 1) {
        return;
    }

    Node<Transformation*>* prev = nullptr;
    Node<Transformation*>* current = headPtr_;
    Node<Transformation*>* next = nullptr;

    while (current != nullptr) {
        next = current -> getNext();
        current -> setNext(prev);
        prev = current;
        current = next;
    }

    headPtr_ = prev;
}

/**
 * @param type: The string type to remove (e.g., "SCALE" or "TRANSLATE").
 * @post: All transformations matching the given type are removed from the pipeline and  * @return: The number of transformations removed.
 */
int TransformationPipeline::removeTransformationsOfType(const std::string& type) {
    int count = 0;
    int i = 1;

    while (i <= getLength()) {
        Transformation* t = getEntry(i);

        if (t -> getType() == type) {
            remove(i);
            delete t;
            count++;
        } 
        
        else {
            i++;
        }
    }

    return count;
}
