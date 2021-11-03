class Solution {
    public int solution(int[][] sizes) {
        int answer = 0;
        int width = sizes[0][0];
        int height = sizes[0][1];
        int max = 0;
        
        for (int[] size : sizes) {
            if (max < size[0] && size[0] > size[1]) {
                width = size[0];
                height = size[1];
                max = size[0];
            }
            if (max < size[1] && size[1] > size[0]) {
                width = size[0];
                height = size[1];
                max = size[1];
            }
        }
        
        max = 0;
        
        for (int[] size : sizes) {
            max = Math.max(max, Math.min(size[0], size[1]));
        }
        
        if (width > height) {
            return max * width;
        }
        
        if (width < height) {
            return max * height;
        }
        return width * height;
    }
}