<template>
  <div id="wapper">
    <el-dialog
      title="上传一张图片"
      width="40%"
      v-model="needUpload"
      :before-close="checkUpload"
    >
      <el-upload
        action="#"
        list-type="picture-card"
        :on-change="getFile"
        :on-remove="handleRemove"
        :auto-upload="false"
        :limit="1"
      >
        <i class="el-icon-plus"></i>
      </el-upload>
    </el-dialog>
    <div id="choice-box">
      <div id="choices">
        <el-button
          size="small"
          type="primary"
          @click="openUploadDialog"
          style="margin-right: 20px"
          >上传/更改图片</el-button
        >
        <el-radio v-model="procType" label="0">滤镜</el-radio>
        <el-radio v-model="procType" label="1">锐化</el-radio>
        <el-radio v-model="procType" label="2">对比度</el-radio>
        <el-radio v-model="procType" label="3">美白</el-radio>
        <el-radio v-model="procType" label="4">磨皮</el-radio>
      </div>
      <div v-if="procType == '0'" class="subchoice">
        <el-button @click="doFilter(0)" size="small" type="primary" round
          >毛玻璃</el-button
        >
        <el-button @click="doFilter(1)" size="small" type="primary" round
          >蜡笔画</el-button
        >
        <el-button @click="doFilter(2)" size="small" type="primary" round
          >褪色</el-button
        >
        <el-button @click="doFilter(3)" size="small" type="primary" round
          >去雾</el-button
        >
        <el-button @click="doFilter(5)" size="small" type="primary" round
          >怀旧</el-button
        >
        <el-button @click="doFilter(6)" size="small" type="primary" round
          >素描</el-button
        >
        <el-button @click="doFilter(8)" size="small" type="primary" round
          >浮雕</el-button
        >
      </div>
      <div v-else-if="procType == '1'" class="subchoice slider-box">
        <span class="remind-text">锐化程度</span>
        <el-slider
          v-model="sharpDegree"
          :step="1"
          style="width: 300px; margin-right: 25px"
        >
        </el-slider>
        <el-button size="small" type="primary" icon="el-icon-check" circle />
      </div>
      <div v-else-if="procType == '2'" class="subchoice slider-box">
        <span class="remind-text">对比度</span>
        <el-slider
          v-model="contrastDegree"
          :step="1"
          style="width: 300px; margin-right: 25px"
        >
        </el-slider>
        <el-button size="small" type="primary" icon="el-icon-check" circle />
      </div>
      <div v-else-if="procType == '3'" class="subchoice slider-box">
        <span class="remind-text">美白程度</span>
        <el-slider
          v-model="whiteDegree"
          :step="1"
          style="width: 300px; margin-right: 25px"
        >
        </el-slider>
        <el-button size="small" type="primary" icon="el-icon-check" circle />
      </div>
      <div v-else-if="procType == '4'" class="subchoice slider-box">
        <span class="remind-text">磨皮程度</span>
        <el-slider
          v-model="bufferDegree"
          :step="1"
          max="10"
          style="width: 300px; margin-right: 25px"
        >
        </el-slider>
        <el-button size="small" type="primary" icon="el-icon-check" circle />
      </div>
    </div>
    <div id="image-box">
      <el-image :src="editImage" fit="scale-down">
        <template #error>
          <div style="color: gray; font-size: 15px">
            请上传一张图片
          </div>
        </template>
      </el-image>
    </div>
  </div>
</template>

<script>
import axios from "axios";
import { ElMessage } from "element-plus";

axios.defaults.baseURL = "http://127.0.0.1:18000/imgProc/";

export default {
  data() {
    return {
      needUpload: true,
      hasUpload: false,
      procType: "0",
      sharpDegree: 0,
      contrastDegree: 0,
      whiteDegree: 0,
      bufferDegree: 0,
      editImage: "",
    };
  },
  methods: {
    openUploadDialog() {
      this.needUpload = true;
    },
    checkUpload() {
      if (this.hasUpload == false) {
        ElMessage.warning("请上传一张图片");
        this.needUpload = true;
      } else {
        this.needUpload = false;
      }
    },
    getFile(file) {
      this.getBase64(file.raw).then((res) => {
        const params = res;
        if (params.length > 0) {
          this.editImage = params;
        }
        this.hasUpload = true;
      });
    },
    getBase64(file) {
      return new Promise(function(resolve, reject) {
        const reader = new FileReader();
        let imgResult = "";
        reader.readAsDataURL(file);
        reader.onload = function() {
          imgResult = reader.result;
        };
        reader.onerror = function(error) {
          reject(error);
        };
        reader.onloadend = function() {
          resolve(imgResult);
        };
      });
    },
    handleRemove() {
      this.hasUpload = false;
    },
    doFilter(type) {
      var formData = new FormData();
      formData.append("operation", type);
      formData.append("editedImg", this.editImage);
      this.doPost("filter/", formData);
    },
    doSharp() {
      var formData = new FormData();
      formData.append("sharp_degree", this.sharpDegree);
      formData.append("editedImg", this.editImage);
      this.doPost("changeSharp/", formData);
    },
    doContrast() {
      var formData = new FormData();
      formData.append("contrast_degree", this.contrastDegree);
      formData.append("editedImg", this.editImage);
      this.doPost("changeContrast/", formData);
    },
    doWhite() {
      var formData = new FormData();
      formData.append("white_degree", this.whiteDegree);
      formData.append("editedImg", this.editImage);
      this.doPost("beautify_white/", formData);
    },
    doBuffer() {
      var formData = new FormData();
      formData.append("buffer_degree", this.bufferDegree);
      formData.append("editedImg", this.editImage);
      this.doPost("beautify_buffering/", formData);
    },
    doPost(path, data) {
      axios.post(path, data).then(this.handleSendSuccess, this.handleSendError);
    },
    handleSuccess(response) {
      var code = response.data.error_code;
      if (code != 0) {
        ElMessage.error("出错了！请稍后再试~");
      } else {
        this.editImage = response.data.img_proc_result;
      }
    },
    handleError(error) {
      console.log(error.message);
      ElMessage.error("出错了！请稍后再试~");
    },
  },
};
</script>

<style>
#choice-box {
  width: 60vw;
  height: 160px;
  margin: 20px 20vw 10px 20vw;
  padding: 5px 25px 5px 25px;
  background-color: white;
  border-radius: 5px;
  box-shadow: 0 0 10px 5px rgba(0, 0, 0, 0.3);
}

#choices {
  line-height: 70px;
}
.subchoice {
  margin-top: 10px;
  line-height: 38px;
}
.slider-box {
  display: flex;
}

.remind-text {
  font-size: 15px;
  color: gray;
  margin-right: 25px;
}

#image-box {
  display: flex;
  justify-content: space-around;
  padding: 10px 25px 10px 25px;
  width: 60vw;
  margin: 20px 20vw 10px 20vw;
  height: 450px;
  line-height: 450px;
  background-color: white;
  border-radius: 5px;
  box-shadow: 0 0 10px 5px rgba(0, 0, 0, 0.3);
}
</style>
