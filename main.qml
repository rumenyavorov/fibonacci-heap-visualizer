import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ApplicationWindow {
    visible: true
    title: "Fibonacci Heap Visualizer"
    width: 1400
    height: 800

    ColumnLayout {
        anchors.fill: parent

        // Grey Rectangle as a Header
        Rectangle {
            color: "#f0f0f0" // Light grey color
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
                    text: "Remove Smallest"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.removeSmallest();
                    }
                }

                TextField {
                    id: currentKey
                    placeholderText: "Current Key"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                }

                TextField {
                    id: newKey
                    placeholderText: "New Key"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                }

                Button {
                    text: "Decrease key"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.decreaseKey(parseInt(currentKey.text), parseInt(newKey.text));
                        currentKey.text = "";
                        newKey.text = "";
                    }
                }

                TextField {
                    id: deleteKey
                    placeholderText: "Key to Delete"
                    font.pixelSize: 20
                    Layout.fillWidth: true
                }

                Button {
                    text: "Delete key"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.deleteNode(parseInt(deleteKey.text));
                        deleteKey.text = "";
                    }
                }

                Button {
                    text: "Clear Heap"
                    font.pixelSize: 20
                    onClicked: {
                        fibHeapWrapper.clearHeap();
                    }
                }
            }
        }

        // Canvas for Visualization
        Canvas {
            id: canvas
            Layout.fillWidth: true
            Layout.fillHeight: true

            onPaint: {
                var ctx = canvas.getContext("2d");
                ctx.clearRect(0, 0, width, height);

                var nodeData = fibHeapWrapper.getCurrentNodes();
                var nodes = nodeData.split(',');

                var startX = 50; // Starting x-coordinate for nodes
                var gap = 60;    // Gap between nodes
                var radius = 20; // Radius of each node

                nodes.forEach(function(nodeKey, index) {
                    var x = startX + (index * gap);
                    var y = canvas.height / 2; // Center nodes vertically

                    // Draw node as a circle
                    ctx.beginPath();
                    ctx.arc(x, y, radius, 0, 2 * Math.PI, false);
                    ctx.fillStyle = 'lightblue';
                    ctx.fill();
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = 'black';
                    ctx.stroke();
                    ctx.fillStyle = 'black';
                    ctx.textAlign = 'center';
                    ctx.textBaseline = 'middle';
                    ctx.font = '16px Arial';
                    ctx.fillText(nodeKey, x, y);
                });
            }
        }
    }
    Component.onCompleted: {
        fibHeapWrapper.nodesChanged.connect(canvas.requestPaint);
    }
}
