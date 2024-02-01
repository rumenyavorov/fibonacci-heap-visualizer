import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ApplicationWindow {
    visible: true
    title: "Fibonacci Heap Visualizer"
    width: 1400
    height: 800

    property bool doesNodeExist: false

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            color: "#f0f0f0"
            Layout.fillWidth: true
            height: 100

            RowLayout {
                anchors.fill: parent

                TextField {
                    id: nodeKey
                    placeholderText: "Enter Node Key"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                }

                Button {
                    text: "Insert"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.insert(parseInt(nodeKey.text));
                        nodeKey.text = "";
                    }
                }

                Button {
                    id: removeBtn
                    text: "Remove Smallest"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.removeSmallest();
                    }
                    enabled: doesNodeExist
                }

                TextField {
                    id: currentKey
                    placeholderText: "Current Key"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                    visible: doesNodeExist
                }

                TextField {
                    id: newKey
                    placeholderText: "New Key"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                    visible: doesNodeExist
                }

                Button {
                    id: decreaseBtn
                    text: "Decrease key"
                    font.pixelSize: 20
                    onClicked: {
                        if(parseInt(currentKey.text) > parseInt(newKey.text)){
                            fibHeapWrapper.decreaseKey(parseInt(currentKey.text), parseInt(newKey.text));
                        }
                        currentKey.text = "";
                        newKey.text = "";
                    }
                    enabled: doesNodeExist
                }

                TextField {
                    id: deleteNode
                    placeholderText: "Node to Delete"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                    visible: doesNodeExist
                }

                Button {
                    id: deleteBtn
                    text: "Delete node"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.deleteNode(parseInt(deleteNode.text));
                        deleteNode.text = "";
                    }
                    enabled: doesNodeExist
                }

                Button {
                    id: clearBtn
                    text: "Clear Heap"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.clearHeap();
                    }
                    enabled: doesNodeExist
                }

                Connections {
                    target: fibHeapWrapper
                    onNodesChanged: {
                        doesNodeExist = fibHeapWrapper.getNodes().length > 0;
                    }
                }
            }
        }

        // Canvas for Visualization
        Canvas {
            id: canvas
            Layout.fillWidth: true
            Layout.fillHeight: true

            onPaint: function() {
                var ctx = canvas.getContext("2d");
                ctx.clearRect(0, 0, width, height);

                var nodeData = fibHeapWrapper.getNodes();

                // Define the properties for nodes and drawing dimensions
                var horizontalNodeDistance = 50; // Minimum horizontal distance between nodes
                var arrowLength = 20; // Length of the arrow
                var arrowWidth = 6; // Width of the arrowhead
                var radius = 20; // Radius of each node
                var minDrawn = false; // Flag to for min label

                var maxDegree = 0;
                for (let i = 0; i < nodeData.length; i++) {
                    if (nodeData[i].degree > maxDegree) {
                        maxDegree = nodeData[i].degree;
                    }
                }
                // Dimensions for the array representation
                var arrayElementWidth = 40;
                var arrayElementHeight = 20;
                var totalDegrees = maxDegree + 1; // +1 because degree levels start at 0
                var arrayStartX = (width - (arrayElementWidth * totalDegrees)) / 2; // Center the array horizontally
                var arrayStartY = 10; // Start from the top of the canvas

                // Draw the array representation of the heap's degree
                if(maxDegree > 0) {
                    for (let degree = 0; degree <= maxDegree; degree++) {
                        ctx.strokeRect(arrayStartX + degree * arrayElementWidth, arrayStartY, arrayElementWidth, arrayElementHeight);
                        ctx.textAlign = 'center';
                        ctx.textBaseline = 'middle';
                        ctx.fillText(degree + 1, arrayStartX + degree * arrayElementWidth + arrayElementWidth / 2, arrayStartY + arrayElementHeight / 2);
                    }
                }

                // Function to draw an arrow pointing to the minimum node
                function drawArrow(x, y) {
                    ctx.beginPath();
                    ctx.moveTo(x, y);
                    ctx.lineTo(x, y - arrowLength + 5);
                    ctx.strokeStyle = 'black';
                    ctx.lineWidth = 2;
                    ctx.stroke();
                }

                // Function to draw a single node
                function drawNode(node, x, y, level) {
                    var vGap = 50; // Vertical gap between levels

                    // Draw the node as a circle
                    ctx.beginPath();
                    ctx.arc(x, y, radius, 0, 2 * Math.PI, false);
                    ctx.fillStyle = 'lightblue';
                    ctx.fill();
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = 'black';
                    ctx.stroke();

                    // Draw the node's key
                    ctx.fillStyle = 'black';
                    ctx.textAlign = 'center';
                    ctx.textBaseline = 'middle';
                    ctx.font = '16px Arial';
                    ctx.fillText(node.key, x, y);

                    // If this is the min node and it has not been drawn yet
                    if (node.isMin && !minDrawn) {
                        ctx.font = 'bold 14px Arial';
                        ctx.fillText("Min", x, y - radius - arrowLength - 20);
                        drawArrow(x, y - radius - 10);
                        minDrawn = true; // Set the flag so no more min labels are drawn
                    }

                    // Recursively draw each child
                    var childGap = radius * 4; // Set a fixed gap between children nodes
                    var childX = x - (childGap * (node.children.length - 1)) / 2;
                    node.children.forEach(function(child) {
                        // Draw line to child
                        ctx.beginPath();
                        ctx.moveTo(x, y + radius);
                        ctx.lineTo(childX, y + vGap - radius);
                        ctx.stroke();

                        // Draw child node
                        drawNode(child, childX, y + vGap, level + 1);
                        childX += childGap;
                    });
                }

                // Calculate total width of the node structure and set starting X position to center it
                var totalNodesWidth = nodeData.reduce(function(acc, node) {
                    return acc + (node.children.length + 1) * (2 * radius + horizontalNodeDistance);
                }, 0);
                var startX = (width - totalNodesWidth) / 2 + radius;
                var startY = arrayStartY + arrayElementHeight + arrowLength + 40; // Y-coordinate for the root nodes, adjusted for arrow and label
                var verticalGap = 100;

                // Draw each root node and its children
                nodeData.forEach(function(rootNode, index) {
                    drawNode(rootNode, startX, startY + verticalGap, 0); // Level is 0 for root nodes

                    // Only draw a line to the next node if it's not the last one
                    if(index < nodeData.length - 1) {
                        var nextNodeX = startX + (rootNode.children.length + 1) * (2 * radius + horizontalNodeDistance);
                        ctx.beginPath();
                        ctx.moveTo(startX + radius, startY + verticalGap);
                        ctx.lineTo((nextNodeX - horizontalNodeDistance / 2) + radius, startY + verticalGap); // End line halfway to the next node
                        ctx.stroke();
                    }

                    // Update startX for the next node
                    startX += (rootNode.children.length + 1) * ((2 * radius) + horizontalNodeDistance); // Move X-coordinate for the next tree
                });
            }

        }
    }
    Component.onCompleted: {
        fibHeapWrapper.nodesChanged.connect(canvas.requestPaint);
    }
}
